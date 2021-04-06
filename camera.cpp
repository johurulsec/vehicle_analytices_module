#include "camera.h"
//#include "PTZControl/Ptz.h"
//#include <X11/Xlib.h>
//#include "AI_src/image.h"
//#include <tesseract/baseapi.h>
//#include <leptonica/allheaders.h>
//#include <cairo/cairo.h>
#include <dlib/opencv.h>
#include <QTextCodec>
//#include <qtconcurrentrun.h>
#include <sstream>
#include <iostream>
#include "rectangle.h"


int imnum =0;

#include <QDebug>
#include <QMutexLocker>
#include "opencv2/opencv.hpp"

//#include <gst/gst.h>
//#include <glib.h>
//#include <stdio.h>
//#include <math.h>
//#include <string.h>
//#include <sys/time.h>

//#include "gstnvdsmeta.h"
////#include "gstnvstreammeta.h"
////#ifndef PLATFORM_TEGRA
//#include "gst-nvmessage.h"
////#endif

//#define MAX_DISPLAY_LEN 64

//#define PGIE_CLASS_ID_VEHICLE 0
//#define PGIE_CLASS_ID_PERSON 2

///* The muxer output resolution must be set if the input streams will be of
// * different resolution. The muxer will scale all the input frames to this
// * resolution. */
//#define MUXER_OUTPUT_WIDTH 1920
//#define MUXER_OUTPUT_HEIGHT 1080

///* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
// * based on the fastest source's framerate. */
//#define MUXER_BATCH_TIMEOUT_USEC 4000000

//#define TILED_OUTPUT_WIDTH 1920
//#define TILED_OUTPUT_HEIGHT 1080

///* NVIDIA Decoder source pad memory feature. This feature signifies that source
// * pads having this capability will push GstBuffers containing cuda buffers. */
//#define GST_CAPS_FEATURES_NVMM "memory:NVMM"

//gchar pgie_classes_str[4][32] = { "Vehicle", "TwoWheeler", "Person",
//  "RoadSign"
//};
//int imgNo;

//int rectL, rectT, rectW, rectH;
//#define FPS_PRINT_INTERVAL 300
////static struct timeval start_time = { };
//std::deque<cv::Mat> frameQueue;
//typedef struct _NvDecoderMeta
//{
//   gchar cat;
//   cv::Mat ass;
//  guint frame_type;
//  guint frame_num;
//  gboolean dec_err;
//} NvDecoderMeta;

////static guint probe_counter = 0;

///* tiler_sink_pad_buffer_probe  will extract metadata received on OSD sink pad
// * and update params for drawing rectangle, object information etc. */

//GstPadProbeReturn Camera::tiler_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data)
//{
//    GstBuffer *buf = (GstBuffer *) info->data;
//    guint num_rects = 0;
//    NvDsObjectMeta *obj_meta = NULL;
//    guint vehicle_count = 0;
//    guint person_count = 0;
//    NvDsMetaList * l_frame = NULL;
//    NvDsMetaList * l_obj = NULL;
//    NvDsDisplayMeta *display_meta = NULL;
//     NvDecoderMeta * decoder_meta = NULL;
//    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
//    NvDsMetaList * l_user_meta = NULL;
//    NvDsUserMeta *user_meta = NULL;

//    for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
//      l_frame = l_frame->next) {
//        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) (l_frame->data);
//        //int offset = 0;
//        for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
//                l_obj = l_obj->next) {
//            obj_meta = (NvDsObjectMeta *) (l_obj->data);
////            if (obj_meta->class_id == PGIE_CLASS_ID_VEHICLE) {
////                vehicle_count++;
////                num_rects++;
////            }
////            if (obj_meta->class_id == PGIE_CLASS_ID_PERSON) {
////                person_count++;
////                num_rects++;
////            }

//                        rectL = obj_meta->rect_params.left;

//                        rectT = obj_meta->rect_params.top;

//                         rectW = obj_meta->rect_params.width;
//                rectH = obj_meta->rect_params.height;

//            for (l_user_meta = obj_meta->obj_user_meta_list; l_user_meta != NULL;
//                l_user_meta = l_user_meta->next) {
//              user_meta = (NvDsUserMeta *) (l_user_meta->data);
//             // user_meta_data = (gchar *)user_meta->user_meta_data;

//             // if(user_meta->base_meta.meta_type == NVDS_USER_FRAME_META_EXAMPLE)
//             // {
//                  decoder_meta = (NvDecoderMeta *)user_meta->user_meta_data;


//               g_print("Dec Meta retrieved as NVDS USER METADTA For Frame_Num = %d Cat value= %c \n",
//                        decoder_meta->frame_num, decoder_meta->cat);
//                    g_print("frame type = %d, frame_num = %d decode_error_status = %d\n\n",
//                        decoder_meta->frame_type, decoder_meta->frame_num,
//                        decoder_meta->dec_err);
//                    std::string patH = "/home/sigmind/Pictures/qtCrop/frame_" + std::to_string(imgNo) +  ".jpg";
//                                cv::Mat received = decoder_meta->ass;
//                                QString metaaa = " Balchal";
//                                frameQueue.push_back(received.clone());
//                               // DSaddFace_triggered(received, 5);
//                              //  emit ui->emitDSFace(received, 5);

//                               // reinterpret_cast<MainWindow*>(userData)->emitBlink();

//                                //warkeaddFace_triggered(received, 5);
//                              //  warker->doWark(received, metaaa, 2);
//                              //  this->addFace_triggered(QPixmap, int);
//                              //  cv::imwrite(patH, received);
//                                received.release();
//                                  imgNo++;

//                g_print("\n");
//              }


//        }
////          g_print ("Frame Number = %d Number of objects = %d "
////            "Vehicle Count = %d Person Count = %d\n",
////            frame_meta->frame_num, num_rects, vehicle_count, person_count);
//#if 0
//        display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
//        NvOSD_TextParams *txt_params  = &display_meta->text_params;
//        txt_params->display_text = g_malloc0 (MAX_DISPLAY_LEN);
//        offset = snprintf(txt_params->display_text, MAX_DISPLAY_LEN, "Person = %d ", person_count);
//        offset = snprintf(txt_params->display_text + offset , MAX_DISPLAY_LEN, "Vehicle = %d ", vehicle_count);

//        /* Now set the offsets where the string should appear */
//        txt_params->x_offset = 10;
//        txt_params->y_offset = 12;

//        /* Font , font-color and font-size */
//        txt_params->font_params.font_name = "Serif";
//        txt_params->font_params.font_size = 10;
//        txt_params->font_params.font_color.red = 1.0;
//        txt_params->font_params.font_color.green = 1.0;
//        txt_params->font_params.font_color.blue = 1.0;
//        txt_params->font_params.font_color.alpha = 1.0;

//        /* Text background color */
//        txt_params->set_bg_clr = 1;
//        txt_params->text_bg_clr.red = 0.0;
//        txt_params->text_bg_clr.green = 0.0;
//        txt_params->text_bg_clr.blue = 0.0;
//        txt_params->text_bg_clr.alpha = 1.0;

//        nvds_add_display_meta_to_frame(frame_meta, display_meta);
//#endif

//    }
//    return GST_PAD_PROBE_OK;
//}

//gboolean Camera::bus_call (GstBus * bus, GstMessage * msg, gpointer data)
//{
//  GMainLoop *loop = (GMainLoop *) data;
//  switch (GST_MESSAGE_TYPE (msg)) {
//    case GST_MESSAGE_EOS:
//      g_print ("End of stream\n");
//      g_main_loop_quit (loop);
//            g_print ("Returned, stopping playback\n");
////            gst_element_set_state (pipeline, GST_STATE_NULL);
////            g_print ("Deleting pipeline\n");
////            gst_object_unref (GST_OBJECT (pipeline));
////            g_source_remove (bus_watch_id);
//            g_main_loop_unref (loop);

//      break;
//    case GST_MESSAGE_WARNING:
//    {
//      gchar *debug;
//      GError *error;
//      gst_message_parse_warning (msg, &error, &debug);
//      g_printerr ("WARNING from element %s: %s\n",
//          GST_OBJECT_NAME (msg->src), error->message);
//      g_free (debug);
//      g_printerr ("Warning: %s\n", error->message);
//      g_error_free (error);
//      break;
//    }
//    case GST_MESSAGE_ERROR:
//    {
//      gchar *debug;
//      GError *error;
//      gst_message_parse_error (msg, &error, &debug);
//      g_printerr ("ERROR from element %s: %s\n",
//          GST_OBJECT_NAME (msg->src), error->message);
//      if (debug)
//        g_printerr ("Error details: %s\n", debug);
//      g_free (debug);
//      g_error_free (error);
//      g_main_loop_quit (loop);
//      break;
//    }
////#ifndef PLATFORM_TEGRA
//    case GST_MESSAGE_ELEMENT:
//    {
//      if (gst_nvmessage_is_stream_eos (msg)) {
//        guint stream_id;
//        if (gst_nvmessage_parse_stream_eos (msg, &stream_id)) {
//          g_print ("Got EOS from stream %d\n", stream_id);
//        }
//      }
//      break;
//    }
////#endif
//    default:
//      break;
//  }
//  return TRUE;
//}

//static void
//cb_newpad (GstElement * decodebin, GstPad * decoder_src_pad, gpointer data)
//{
//  g_print ("In cb_newpad\n");
//  GstCaps *caps = gst_pad_get_current_caps (decoder_src_pad);
//  const GstStructure *str = gst_caps_get_structure (caps, 0);
//  const gchar *name = gst_structure_get_name (str);
//  GstElement *source_bin = (GstElement *) data;
//  GstCapsFeatures *features = gst_caps_get_features (caps, 0);

//  /* Need to check if the pad created by the decodebin is for video and not
//   * audio. */
//  if (!strncmp (name, "video", 5)) {
//    /* Link the decodebin pad only if decodebin has picked nvidia
//     * decoder plugin nvdec_*. We do this by checking if the pad caps contain
//     * NVMM memory features. */
//    if (gst_caps_features_contains (features, GST_CAPS_FEATURES_NVMM)) {
//      /* Get the source bin ghost pad */
//      GstPad *bin_ghost_pad = gst_element_get_static_pad (source_bin, "src");
//      if (!gst_ghost_pad_set_target (GST_GHOST_PAD (bin_ghost_pad),
//              decoder_src_pad)) {
//        g_printerr ("Failed to link decoder src pad to source bin ghost pad\n");
//      }
//      gst_object_unref (bin_ghost_pad);
//    } else {
//      g_printerr ("Error: Decodebin did not pick nvidia decoder plugin.\n");
//    }
//  }
//}

//static void
//decodebin_child_added (GstChildProxy * child_proxy, GObject * object,
//    gchar * name, gpointer user_data)
//{
//  g_print ("Decodebin child added: %s\n", name);
//  if (g_strrstr (name, "decodebin") == name) {
//    g_signal_connect (G_OBJECT (object), "child-added",
//        G_CALLBACK (decodebin_child_added), user_data);
//  }
//  if (g_strstr_len (name, -1, "nvv4l2decoder") == name) {
//    g_print ("Seting bufapi_version\n");
//    g_object_set (object, "bufapi-version", TRUE, NULL);
//  }
//}

//static GstElement *
//create_source_bin (guint index, gchar * uri)
//{
//  GstElement *bin = NULL, *uri_decode_bin = NULL;
//  gchar bin_name[16] = { };

//  g_snprintf (bin_name, 15, "source-bin-%02d", index);
//  /* Create a source GstBin to abstract this bin's content from the rest of the
//   * pipeline */
//  bin = gst_bin_new (bin_name);

//  /* Source element for reading from the uri.
//   * We will use decodebin and let it figure out the container format of the
//   * stream and the codec and plug the appropriate demux and decode plugins. */
//  uri_decode_bin = gst_element_factory_make ("uridecodebin", "uri-decode-bin");

//  if (!bin || !uri_decode_bin) {
//    g_printerr ("One element in source bin could not be created.\n");
//    return NULL;
//  }

//  /* We set the input uri to the source element */
//  g_object_set (G_OBJECT (uri_decode_bin), "uri", uri, NULL);

//  /* Connect to the "pad-added" signal of the decodebin which generates a
//   * callback once a new pad for raw data has beed created by the decodebin */
//  g_signal_connect (G_OBJECT (uri_decode_bin), "pad-added",
//      G_CALLBACK (cb_newpad), bin);
//  g_signal_connect (G_OBJECT (uri_decode_bin), "child-added",
//      G_CALLBACK (decodebin_child_added), bin);

//  gst_bin_add (GST_BIN (bin), uri_decode_bin);

//  /* We need to create a ghost pad for the source bin which will act as a proxy
//   * for the video decoder src pad. The ghost pad will not have a target right
//   * now. Once the decode bin creates the video decoder and generates the
//   * cb_newpad callback, we will set the ghost pad target to the video decoder
//   * src pad. */
//  if (!gst_element_add_pad (bin, gst_ghost_pad_new_no_target ("src",
//              GST_PAD_SRC))) {
//    g_printerr ("Failed to add ghost pad in source bin\n");
//    return NULL;
//  }

//  return bin;
//}


Camera::Camera(int cam_indx, int index, QMutex *par, int pri, QObject *parent)

{
    parent_mutex = par;
    camera_index = cam_indx;
    cap_index = index;
    mutx = new QMutex();
    search_mutex = new QMutex();
    gpu_indx = 0;
    hier_thresh=.5;
    prior = pri;
    //-----------------moved to thread--------------//
    //    thread = new QThread();
    //    worker = new Worker();

    //    worker->moveToThread(thread);
    //    connect(worker, SIGNAL(valueChanged(QString)), this, SLOT(addNewLPR(QString)));
    //    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    //   // connect(thread, SIGNAL(started()), worker, SLOT(doWork(QString)));
    //    connect(this, SIGNAL(requestUpdateLPR(QString)), worker, SLOT(doWork(QString)));
    //    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    //     connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);
    cap = new VideoCapture(index);
    printf("camera index  %d\n\n",camera_index);
    if(cap!= NULL && cap->isOpened()) printf("cap found %d\n\n",camera_index);
    generator= new Producer(cap,mutx,matt, camera_index);
    //processor= new Consumer(cap,mutx,mat,ql);
    //init(gpu_indx);
    //connect(processor,SIGNAL(processed(QPixmap)), this, SLOT(ui_response(QPixmap)));
    connect(this, SIGNAL(start_producer()), generator, SLOT(start()));
    connect(generator, SIGNAL(started()), this, SLOT(inf_loop()));
}

Camera::Camera(int cam_indx, const char *file, QMutex *par, int pri, QObject *parent)
// QObject(parent)
{
    parent_mutex = par;
    camera_index = cam_indx;
    cap_string = (char*) malloc(100);
    strcpy(cap_string, file);
    mutx = new QMutex();
    search_mutex = new QMutex();
    gpu_indx = 0;
    prior = pri;
    hier_thresh=.5;
    //................moved to thread.................//
    //    thread = new QThread();
    //    worker = new Worker();

    //    worker->moveToThread(thread);
    //    connect(worker, SIGNAL(valueChanged(QString)), this, SLOT(addNewLPR(QString)));
    //    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));
    //    //connect(thread, SIGNAL(started()), worker, SLOT(doWork(QString)));
    //    connect(this, SIGNAL(requestUpdateLPR(QString)), worker, SLOT(doWork(QString)));
    //    connect(worker, SIGNAL(finished()), thread, SLOT(quit()), Qt::DirectConnection);

    cap = new VideoCapture(file);
    if(!cap->isOpened()) //qDebug()<<"not opened\n\n";
    generator= new Producer(cap,mutx,matt, camera_index);
    //processor= new Consumer(cap,mutx,mat,ql);
    //    init(gpu_indx);
    //connect(processor,SIGNAL(processed(QPixmap)), this, SLOT(ui_response(QPixmap)));
    connect(this, SIGNAL(start_producer()), generator, SLOT(start()));
    connect(generator, SIGNAL(started()), this, SLOT(inf_loop()));

}

Camera::~Camera()
{
    generator->may_day();
    generator->wait();
    delete generator;
    //    worker->abort();
    //    thread->wait();
    //    //qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    //    delete thread;
    //    delete worker;
    if(cap!= NULL)
    {
        delete cap;
    }
    //qDebug()<<"cap released\n";
    if(cap_string) free(cap_string);
    if(mutx!=NULL) delete mutx;
    //  //qDebug()<<"mutx deleted\n";
    // if(options!=NULL) free(options);
    //if(FR!=NULL) delete FR;
    //qDebug()<<"FR deleted\n";
    //    if(name_list) free(name_list);
    //    //qDebug()<<"namelist freed\n";
    // free_network(net);
    // //qDebug()<<"net deleted\n";
    //    for(int i=0; i<8; i++)
    //    {
    //        free(alphabet[i]);
    //    }

    //frameQueue.clear();



    //    g_print ("Returned, stopping playback\n");
    //    gst_element_set_state (pipeline, GST_STATE_NULL);
    //    g_print ("Deleting pipeline\n");
    //    gst_object_unref (GST_OBJECT (pipeline));
    //    g_source_remove (bus_watch_id);
    // g_main_loop_unref (loop);

}

void Camera::sendToUI(cv::Mat mat, cv::Mat orig, std::vector<watchcam::rectangle > rects)
{
    //emit ui_go(mat, orig, rects);
}

void Camera::reset_object_threshold(double x)
{
    //qDebug() << "x value in cam " << x;
    parent_mutex->lock();
    thresh = hier_thresh*(1.0- x);
    //qDebug() << "hier thresh " << hier_thresh;
    parent_mutex->unlock();

}

void Camera::end()
{
    _abort = true;
}

//void Camera::face_database_update()
//{
//    //................may have to add mutex................//
//    if(FR!=NULL)
//    {
//        FR->setup(face_names, face_descriptors);
//    }
//}

void Camera::start()
{
    printf("starting...\n");
    emit start_requested();
}

void Camera::go()
{
    printf("going...\n");
    //generator->start();
    emit start_producer();
}



void Camera::inf_loop()
{
    int countr=0;
    printf("inf loop for camera: %d\n\n",camera_index);
    //  namedWindow("edges",1);
    //init(gpu_indx, prior);  // Paisi
    init(gpu_indx, prior);
    //face_database_update();
    //    generator->start();

    while(true)
    {
        if(_abort) break;
        //        printf("started  %d\n\n", camera_index);
        if(cap==NULL || !cap->isOpened())
        {
            printf("cap not found  %d\n\n",camera_index);
            QThread::msleep(50);
            continue;
        }
        cv::Mat mat,omat;
        bool found = false;
        // mat, omat;
        //            printf("camera no: %d >>> trying to lock mutex from consumer\n", camera_index);
        //while(!mutx->tryLock());
        mutx->lock();
        //            printf("camera no: %d >>> mutex locked from consumer\n", camera_index);
        //mat = matt.clone();
        cap->read(mat);
        //            printf("camera no: %d >>> mat saved in consumer\n", camera_index);
        mutx->unlock();
        //            printf("camera no: %d >>> mutex unlocked in consumer\n", camera_index);

        //        printf("grabed\n\n");
        if(!mat.data)
        {
            printf("no data!\n");
            return;
        }


        std::vector< watchcam::rectangle > rects;


        // std::vector<dlib::matrix<float,(long)0,(long)1>> pic_templates;
        //if (camera_index==0 || camera_index==1)
        if(true)
        {

            //     parent_mutex->lock();


            // g_main_iteration(true);


            //qDebug() << " Inside while loop shuvom";
            // TODO: synchronize...

            cv::Mat frameSinK;
            //            if (frameQueue.size() > 0) {
            //                //qDebug() << " Frame Que  found with image";
            //              // this lags pretty badly even when grabbing frames from webcam
            //              frameSinK = frameQueue.front();
            //       // imwrite("/home/sigmind/Pictures/qtCrop/frame.jpg", frameSinK);

            ////              //  //qDebug() << " Rectangle param --------- from frameSink " << "-- Left: " << QString::number(rectS[1].left) ;
            //              frameQueue.clear();
            //               }
            //            else
            //            {
            //                // frameQueue.clear();
            //                         cv::Mat razor = cv::imread("/home/sigmind/razor.jpg");
            //                frameSinK = razor;
            //            }

            //            //qDebug() << QTime::currentTime().toString() << "YOU MESSED UP in while loop ";
            //            //qDebug() << Q_FUNC_INFO << QDateTime::currentMSecsSinceEpoch();

            //  imshow("edges", frameSink);

            cv::Mat razor = cv::imread("/home/sigmind/Music/deepstream_sdk_v4.0.1_jetson/samples/streams/sample_720p.jpg");

            //   parent_mutex->unlock();

            //qDebug() << " GST Main loop running... ";


            //    time=clock();
            //            omat = image_to_Mat(sized, sized.w, sized.h, sized.c);



            //            omat = image_to_Mat(im, im.w, im.h, im.c);


            //            //........free things...........
            //            free_image(im);
            //            free_image(sized);
            //            free(boxes);
            //            for(int j = 0; j < l.w*l.h*l.n; ++j) free(probs[j]);
            //            free(probs);
            omat = razor;
            razor.release();

            //  frameSink.release();
        }
        else omat = mat;
        //  g_main_iteration(false);
        //vector<int> vect2(vect1);
        // rects = rectS;
        emit ui_go(omat, mat, rects);
        omat.release();
        mat.release();
        //frameQueue.clear();   // This might cause lag or jitter
        // rects.clear();
    }
    printf("ending!\n");
}

//std::vector< watchcam::rectangle > Camera::rect_value(std::vector< watchcam::rectangle > rectS)
//{
//    return rectS;
//}


void Camera::ui_response(QPixmap img)
{
    printf("ui response called!  image size: %dx%d\n\n", img.height(),img.width());
    //    emit ui_go(img, false);
}




void Camera::init(int gpu_indx, int prior)
{
    printf("init started\n\n");



    // ++++++++++++++++++++++++++++++++++++++++++++ DS 4 +++++++++++++++++++++++++++++++++++++++++


    //    // Deadly Hack Injection



    //    //  gchar videos[4][100] = {"file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4"}

    ////      gchar *videos = (gchar*)g_malloc0(4);
    ////        videos[0] = "file:///home/sigmind/sample_10-normal.mp4";

    ////      QString newVid = "file:///home/sigmind/sample_10-normal.mp4";
    ////      QByteArray ba;
    ////      ba = newVid.toUtf8();
    ////      gchar* videos = ba.constData();

    //        gboolean fullFrame = FALSE;

    //      /* Check input arguments */

    //      num_sources =  1;

    //      /* Standard GStreamer initialization */
    //      gst_init (0, NULL);
    //      loop = g_main_loop_new (NULL, FALSE);

    //      /* Create gstreamer elements */
    //      /* Create Pipeline element that will form a connection of other elements */
    //      pipeline = gst_pipeline_new ("dstest3-pipeline");

    //      /* Create nvstreammux instance to form batches from one or more sources. */
    //      streammux = gst_element_factory_make ("nvstreammux", "stream-muxer");

    //      if (!pipeline || !streammux) {
    //        g_printerr ("One element could not be created. Exiting.\n");
    //        //return -1;
    //      }
    //      gst_bin_add (GST_BIN (pipeline), streammux);

    //      gchar* videos[] = {"file:///home/sigmind/shyamoli-face.mp4","file:///home/sigmind/shyamoli-face.mp4", NULL} ;


    //      for (i = 0; i < num_sources; i++) {
    //        GstPad *sinkpad, *srcpad;
    //        gchar pad_name[16] = { };


    //        GstElement *source_bin = create_source_bin (i, videos[i]);

    //        if (!source_bin) {
    //          g_printerr ("Failed to create source bin. Exiting.\n");
    //        //  return -1;
    //        }

    //        gst_bin_add (GST_BIN (pipeline), source_bin);

    //        g_snprintf (pad_name, 15, "sink_%u", i);
    //        sinkpad = gst_element_get_request_pad (streammux, pad_name);
    //        if (!sinkpad) {
    //          g_printerr ("Streammux request sink pad failed. Exiting.\n");
    //         // return -1;
    //        }

    //        srcpad = gst_element_get_static_pad (source_bin, "src");
    //        if (!srcpad) {
    //          g_printerr ("Failed to get src pad of source bin. Exiting.\n");
    //         // return -1;
    //        }

    //        if (gst_pad_link (srcpad, sinkpad) != GST_PAD_LINK_OK) {
    //          g_printerr ("Failed to link source bin to stream muxer. Exiting.\n");
    //        //  return -1;
    //        }

    //        gst_object_unref (srcpad);
    //        gst_object_unref (sinkpad);
    //      }

    //      /* Use nvinfer to infer on batched frame. */
    //      pgie = gst_element_factory_make ("nvinfer", "primary-nvinference-engine");

    //      /* Use nvtiler to composite the batched frames into a 2D tiled array based
    //       * on the source of the frames. */
    //      tiler = gst_element_factory_make ("nvmultistreamtiler", "nvtiler");

    //      /* Use convertor to convert from NV12 to RGBA as required by nvosd */
    //      nvvidconv = gst_element_factory_make ("nvvideoconvert", "nvvideo-converter");

    //      /* Create OSD to draw on the converted RGBA buffer */
    //      nvosd = gst_element_factory_make ("nvdsosd", "nv-onscreendisplay");

    //     dsExample = gst_element_factory_make ("dsexample", "deepstream-example");

    //      /* Finally render the osd output */
    //    //#ifdef PLATFORM_TEGRA
    //    //  transform = gst_element_factory_make ("nvegltransform", "nvegl-transform");
    //      transform = gst_element_factory_make ("queue", "queue");
    //    //#endif
    //      //sink = gst_element_factory_make ("nveglglessink", "nvvideo-renderer");

    //      sink = gst_element_factory_make ("nvoverlaysink", "nvvideo-renderer");

    //      if (!pgie || !tiler || !nvvidconv || !nvosd || !sink) {
    //        g_printerr ("One element could not be created. Exiting.\n");
    //      //  return -1;
    //      }

    //    //#ifdef PLATFORM_TEGRA
    //      if(!transform) {
    //        g_printerr ("One tegra element could not be created. Exiting.\n");
    //      //  return -1;
    //      }
    //    //#endif
    //     g_object_set (G_OBJECT(sink), "sync", FALSE, NULL);
    //// overlay-x=0 overlay-y=0 overlay-w=1280 overlay-h=720 overlay=1
    //     g_object_set (G_OBJECT (dsExample),
    //             "full-frame", fullFrame, NULL);

    //     g_object_set(G_OBJECT(sink), "overlay-x", 50, "overlay-y", 50, "overlay-w", 640, "overlay-h", 480, "overlay", 1, NULL);

    //      g_object_set (G_OBJECT (streammux), "width", MUXER_OUTPUT_WIDTH, "height",
    //          MUXER_OUTPUT_HEIGHT, "batch-size", num_sources,
    //          "batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC, NULL);

    //      /* Configure the nvinfer element using the nvinfer config file. */
    //      g_object_set (G_OBJECT (pgie),
    //          "config-file-path", "/home/sigmind/redaction_with_deepstream/configs/pgie_config_fd_lpd.txt", NULL);

    //      /* Override the batch-size set in the config file with the number of sources. */
    //      g_object_get (G_OBJECT (pgie), "batch-size", &pgie_batch_size, NULL);
    //      if (pgie_batch_size != num_sources) {
    //        g_printerr
    //            ("WARNING: Overriding infer-config batch-size (%d) with number of sources (%d)\n",
    //            pgie_batch_size, num_sources);
    //        g_object_set (G_OBJECT (pgie), "batch-size", num_sources, NULL);
    //      }

    //      tiler_rows = (guint) sqrt (num_sources);
    //      tiler_columns = (guint) ceil (1.0 * num_sources / tiler_rows);
    //      /* we set the tiler properties here */
    //      g_object_set (G_OBJECT (tiler), "rows", tiler_rows, "columns", tiler_columns,
    //          "width", TILED_OUTPUT_WIDTH, "height", TILED_OUTPUT_HEIGHT, NULL);

    //      /* we add a message handler */
    //      bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    //      bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
    //      gst_object_unref (bus);

    //      /* Set up the pipeline */
    //      /* we add all elements into the pipeline */
    //   // #ifdef PLATFORM_TEGRA
    //      gst_bin_add_many (GST_BIN (pipeline), pgie, tiler, nvvidconv, dsExample, nvosd, transform, sink,
    //          NULL);
    //      /* we link the elements together
    //       * nvstreammux -> nvinfer -> nvtiler -> nvvidconv -> nvosd -> video-renderer */
    //      if (!gst_element_link_many (streammux, pgie, tiler, nvvidconv, dsExample, nvosd, transform, sink,
    //              NULL)) {
    //        g_printerr ("Elements could not be linked. Exiting.\n");
    //      //  return -1;
    //      }
    ////    #else
    ////    gst_bin_add_many (GST_BIN (pipeline), pgie, tiler, nvvidconv, nvosd, sink,
    ////          NULL);
    ////      /* we link the elements together
    ////       * nvstreammux -> nvinfer -> nvtiler -> nvvidconv -> nvosd -> video-renderer */
    ////      if (!gst_element_link_many (streammux, pgie, tiler, nvvidconv, nvosd, sink,
    ////              NULL)) {
    ////        g_printerr ("Elements could not be linked. Exiting.\n");
    ////        return -1;
    ////      }
    ////    #endif

    //      /* Lets add probe to get informed of the meta data generated, we add probe to
    //       * the sink pad of the osd element, since by that time, the buffer would have
    //       * had got all the metadata. */
    //      tiler_src_pad = gst_element_get_static_pad (nvosd, "src");
    //      if (!tiler_src_pad)
    //        g_print ("Unable to get src pad\n");
    //      else
    //        gst_pad_add_probe (tiler_src_pad, GST_PAD_PROBE_TYPE_BUFFER,
    //            tiler_src_pad_buffer_probe, NULL, NULL);



    //      /* Set the pipeline to "playing" state */
    ////      g_print ("Now playing:");
    ////      for (i = 0; i < num_sources; i++) {
    ////        g_print (" %s,", argv[i + 1]);
    ////      }
    //      g_print ("\n");
    //      gst_element_set_state (pipeline, GST_STATE_PLAYING);

    //      /* Wait till pipeline encounters an error or EOS */
    //      g_print ("Running...\n");
    //     // g_main_loop_run (loop);
    //     // while(1) {
    //    //  g_main_iteration(false);
    //    //  if (frameQueue.size() > 0) {
    //                      //qDebug() << " Frame size CV  ............ shuvom";

    ////                    cv::Mat frameSinK = frameQueue.front();
    ////                   // cv::cvtColor(srcRgba , src , CV_RGBA2RGB);
    ////                    emit emitDSFace(frameSinK, 5);

    ////                    //cv::imwrite(patH, frameSinK);
    ////                    frameSinK.release();
    ////                    frameQueue.clear();
    //                    //imNo++;
    //     // }


    //      //}
    //      /* Out of the main loop, clean up nicely */


}
