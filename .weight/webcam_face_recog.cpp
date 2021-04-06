// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
Compile with g++ -std=c++11 -O3 -I.. ../dlib/all/source.cpp -lpthread -lX11 -ljpeg -DDLIB_JPEG_SUPPORT webcam_face_recog.cpp $(pkg-config --cflags --libs opencv)

Run with ./a.out
    This example program shows how to find frontal human faces in an image and
    estimate their pose.  The pose takes the form of 68 landmarks.  These are
    points on the face such as the corners of the mouth, along the eyebrows, on
    the eyes, and so forth.  
    

    This example is essentially just a version of the face_landmark_detection_ex.cpp
    example modified to use OpenCV's VideoCapture object to read from a camera instead 
    of files.


    Finally, note that the face detector is fastest when compiled with at least
    SSE2 instructions enabled.  So if you are using a PC with an Intel or AMD
    chip then you should enable at least SSE2 instructions.  If you are using
    cmake to compile this program you can enable them by using one of the
    following commands when you create the build project:
        cmake path_to_dlib_root/examples -DUSE_SSE2_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_SSE4_INSTRUCTIONS=ON
        cmake path_to_dlib_root/examples -DUSE_AVX_INSTRUCTIONS=ON
    This will set the appropriate compiler options for GCC, clang, Visual
    Studio, or the Intel compiler.  If you are using another compiler then you
    need to consult your compiler's manual to determine how to enable these
    instructions.  Note that AVX is the fastest but requires a CPU from at least
    2011.  SSE4 is the next fastest and is supported by most current machines.  
*/

#include <dlib/opencv.h>
#include <opencv2/highgui/highgui.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <iostream>
#include <string>

using namespace dlib;
using namespace std;

// ----------------------------------------------------------------------------------------

// The next bit of code defines a ResNet network.  It's basically copied
// and pasted from the dnn_imagenet_ex.cpp example, except we replaced the loss
// layer with loss_metric and made the network somewhat smaller.  Go read the introductory
// dlib DNN examples to learn what all this stuff means.
//
// Also, the dnn_metric_learning_on_images_ex.cpp example shows how to train this network.
// The dlib_face_recognition_resnet_model_v1 model used by this example was trained using
// essentially the code shown in dnn_metric_learning_on_images_ex.cpp except the
// mini-batches were made larger (35x15 instead of 5x5), the iterations without progress
// was set to 10000, the jittering you can see below in jitter_image() was used during
// training, and the training dataset consisted of about 3 million images instead of 55.
// Also, the input layer was locked to images of size 150.
template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2,2,2,2,skip1<tag2<block<N,BN,2,tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET> 
using block  = BN<con<N,3,3,1,1,relu<BN<con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128,avg_pool_everything<
                            alevel0<
                            alevel1<
                            alevel2<
                            alevel3<
                            alevel4<
                            max_pool<3,3,2,2,relu<affine<con<32,7,7,2,2,
                            input_rgb_image_sized<150>
                            >>>>>>>>>>>>;

// ----------------------------------------------------------------------------------------

std::vector<matrix<rgb_pixel>> jitter_image(
    const matrix<rgb_pixel>& img
);

// ----------------------------------------------------------------------------------------


void GetFilesInDirectory(std::vector<string> &out, const string &directory)
{
#ifdef WINDOWS
    HANDLE dir;
    WIN32_FIND_DATA file_data;

    if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
        return; /* No files found */

    do {
        const string file_name = file_data.cFileName;
        const string full_file_name = directory + "/" + file_name;
        const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

        if (file_name[0] == '.')
            continue;

        if (is_directory)
            continue;

        out.push_back(full_file_name);
    } while (FindNextFile(dir, &file_data));

    FindClose(dir);
#else
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(directory.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = directory + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

        if (is_directory)
            continue;

        out.push_back(file_name);
        out.push_back(full_file_name);
    }
    closedir(dir);
#endif
} // GetFilesInDirectory


int main()
{
    try
    {

		std::vector<string> names;
		GetFilesInDirectory(names,"./faces/template");

		for(int i=0; i<names.size(); i++) cout<< names[i]<<endl;


		//cv::VideoCapture cap("/home/sigmind/hold-my-beer.mp4");
		cv::VideoCapture cap("/home/imran/Music/deepstream_sdk_v4.0.1_jetson/samples/streams/mark.mp4");
        //cv::VideoCapture cap("rtsp://admin:00125680Shuvom@192.168.0.106/Streaming/Channels/1");
		//cap.set(CV_CAP_PROP_BUFFERSIZE, 3);
        if (!cap.isOpened())
        {
            cerr << "Unable to connect to camera" << endl;
            return 1;
        }

        image_window win;

        // Load face detection and pose estimation models.
        frontal_face_detector detector = get_frontal_face_detector();
        // We will also use a face landmarking model to align faces to a standard pose:  (see face_landmark_detection_ex.cpp for an introduction)
		shape_predictor sp;
		deserialize("LM-5p.dat") >> sp;

		// And finally we load the DNN responsible for face recognition.
		anet_type net;
		deserialize("FR-Resnetv2.dat") >> net;

		printf("loading done!\n\n");

		std::vector<matrix<rgb_pixel>> templates;
		matrix<rgb_pixel> temp;
		for(int i=1; i<names.size(); i+=2)
		{
			printf("i : %d\n",i);
			load_image(temp, names[i]);
			printf("debug 0\n");

			for (auto face : detector(temp))
			{
				auto shape = sp(temp, face);
				printf("debug 1\n");
				matrix<rgb_pixel> face_chip;
				extract_image_chip(temp, get_face_chip_details(shape,150,0.25), face_chip);
				templates.push_back(move(face_chip));
			}
		}
		std::vector<matrix<float,0,1>> template_descriptors = net(templates);

        // Grab and process frames until the main window is closed by the user.
        while(!win.is_closed())
        {
            // Grab a frame
            cv::Mat temp;
			//for(int i=0; i<5; i++) cap>> temp;
            if (!cap.read(temp))
            {
				cout<<"image not found!\n";
                continue;
            }
            // Turn OpenCV's Mat into something dlib can deal with.  Note that this just
            // wraps the Mat object, it doesn't copy anything.  So cimg is only valid as
            // long as temp is valid.  Also don't do anything to temp that would cause it
            // to reallocate the memory which stores the image as that will make cimg
            // contain dangling pointers.  This basically means you shouldn't modify temp
            // while using cimg.
            cv_image<bgr_pixel> img(temp);

			win.clear_overlay();
			win.set_image(img);

            // Run the face detector on the image of our action heroes, and for each face extract a
			// copy that has been normalized to 150x150 pixels in size and appropriately rotated
			// and centered.
			std::vector<matrix<rgb_pixel>> faces;
			std::vector<rectangle> rects = detector(img);
			for (auto face : rects)
			{
				auto shape = sp(img, face);
				matrix<rgb_pixel> face_chip;
				extract_image_chip(img, get_face_chip_details(shape,150,0.25), face_chip);
				faces.push_back(move(face_chip));
				// Also put some boxes on the faces so we can see that the detector is finding
				// them.
				win.add_overlay(face);
			}
            
			if (faces.size() == 0)
			{
				cout << "No faces found in image!" << endl;
				//return 1;
			}
			else
			{
				// This call asks the DNN to convert each face image in faces into a 128D vector.
				// In this 128D vector space, images from the same person will be close to each other
				// but vectors from different people will be far apart.  So we can use these vectors to
				// identify if a pair of images are from the same person or from different people.  
				std::vector<matrix<float,0,1>> face_descriptors = net(faces);


				// In particular, one simple thing we can do is face clustering.  This next bit of code
				// creates a graph of connected faces and then uses the Chinese whispers graph clustering
				// algorithm to identify how many people there are and which faces belong to whom.
				std::vector<sample_pair> edges;
				for (size_t i = 0; i < face_descriptors.size(); ++i)
				{
					for (size_t j = 0; j < template_descriptors.size(); ++j)
					{
						cout<<"i : "<<i<<" j : "<<j<<endl;
						// Faces are connected in the graph if they are close enough.  Here we check if
						// the distance between two face descriptors is less than 0.6, which is the
						// decision threshold the network was trained to use.  Although you can
						// certainly use any other threshold you find useful.
						if (length(face_descriptors[i]-template_descriptors[j]) < 0.5)
						{
							string temp = names[j+j] + "found!!";
							win.add_overlay(dlib::image_window::overlay_rect(rects[i], rgb_pixel(0,255,0),temp));
							cout<< "face no: "<<i<<" similar to : " <<names[j+j]<<endl;
						}
					}
				}

   std::vector<unsigned long> labels;
    const auto num_clusters = chinese_whispers(edges, labels);
    // This will correctly indicate that there are 4 people in the image.
    cout << "number of people found in the image: "<< num_clusters << endl;
    
   
    // Now let's display the face clustering results on the screen.  You will see that it
    // correctly grouped all the faces. 
    std::vector<image_window> win_clusters(num_clusters);
    for (size_t cluster_id = 0; cluster_id < num_clusters; ++cluster_id)
    {
        std::vector<matrix<rgb_pixel>> temp;
        for (size_t j = 0; j < labels.size(); ++j)
        {
            if (cluster_id == labels[j])
                temp.push_back(faces[j]);
        }
        win_clusters[cluster_id].set_title("face cluster " + cast_to_string(cluster_id));
        win_clusters[cluster_id].set_image(tile_images(temp));
    }


				// Finally, let's print one of the face descriptors to the screen.  
				cout << "face descriptor for one face: " << trans(face_descriptors[0]) << endl;

				// It should also be noted that face recognition accuracy can be improved if jittering
				// is used when creating face descriptors.  In particular, to get 99.38% on the LFW
				// benchmark you need to use the jitter_image() routine to compute the descriptors,
				// like so:
				
				//matrix<float,0,1> face_descriptor = mean(mat(net(jitter_image(faces[0]))));
				//cout << "jittered face descriptor for one face: " << trans(face_descriptor) << endl;
				
				// If you use the model without jittering, as we did when clustering the bald guys, it
				// gets an accuracy of 99.13% on the LFW benchmark.  So jittering makes the whole
				// procedure a little more accurate but makes face descriptor calculation slower.
			}

			// Display it all on the screen
            //win.clear_overlay();
            //win.set_image(cimg);
            //win.add_overlay(render_face_detections(shapes));
        }
    }
    catch(serialization_error& e)
    {
        cout << "You need dlib's default face landmarking model file to run this example." << endl;
        cout << "You can get it from the following URL: " << endl;
        cout << "   http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2" << endl;
        cout << endl << e.what() << endl;
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
}

// ----------------------------------------------------------------------------------------

std::vector<matrix<rgb_pixel>> jitter_image(
    const matrix<rgb_pixel>& img
)
{
    // All this function does is make 100 copies of img, all slightly jittered by being
    // zoomed, rotated, and translated a little bit differently.
    thread_local random_cropper cropper;
    cropper.set_chip_dims(150,150);
    cropper.set_randomly_flip(true);
    cropper.set_max_object_size(0.99999);
    cropper.set_background_crops_fraction(0);
    cropper.set_min_object_size(0.97);
    cropper.set_translate_amount(0.02);
    cropper.set_max_rotation_degrees(3);

    std::vector<mmod_rect> raw_boxes(1), ignored_crop_boxes;
    raw_boxes[0] = shrink_rect(get_rect(img),3);
    std::vector<matrix<rgb_pixel>> crops; 

    matrix<rgb_pixel> temp; 
    for (int i = 0; i < 100; ++i)
    {
        cropper(img, raw_boxes, temp, ignored_crop_boxes);
        crops.push_back(move(temp));
    }
    return crops;
}

// ----------------------------------------------------------------------------------------

