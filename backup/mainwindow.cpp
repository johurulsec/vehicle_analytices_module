#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogs/settingsdialog.h>

#include <QDebug>
#include <QFile>


#include <gst/gst.h>
#include <glib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>

#include "gstnvdsmeta.h"
//#include "gstnvstreammeta.h"
//#ifndef PLATFORM_TEGRA
#include "gst-nvmessage.h"
//#endif

#define MAX_DISPLAY_LEN 64

#define PGIE_CLASS_ID_VEHICLE 0
#define PGIE_CLASS_ID_PERSON 2

/* The muxer output resolution must be set if the input streams will be of
 * different resolution. The muxer will scale all the input frames to this
 * resolution. */
#define MUXER_OUTPUT_WIDTH 1920
#define MUXER_OUTPUT_HEIGHT 1080

/* Muxer batch formation timeout, for e.g. 40 millisec. Should ideally be set
 * based on the fastest source's framerate. */
#define MUXER_BATCH_TIMEOUT_USEC 4000000

#define TILED_OUTPUT_WIDTH 1920
#define TILED_OUTPUT_HEIGHT 1080

/* NVIDIA Decoder source pad memory feature. This feature signifies that source
 * pads having this capability will push GstBuffers containing cuda buffers. */
#define GST_CAPS_FEATURES_NVMM "memory:NVMM"

gchar pgie_classes_str[4][32] = { "Vehicle", "TwoWheeler", "Person",
  "RoadSign"
};
int imgNo;

int rectL, rectT, rectW, rectH;
#define FPS_PRINT_INTERVAL 300
//static struct timeval start_time = { };
std::deque<cv::Mat> frameQueue;
typedef struct _NvDecoderMeta
{
   gchar cat;
   cv::Mat ass;
  guint frame_type;
  guint frame_num;
  gboolean dec_err;
} NvDecoderMeta;

//static guint probe_counter = 0;

/* tiler_sink_pad_buffer_probe  will extract metadata received on OSD sink pad
 * and update params for drawing rectangle, object information etc. */

GstPadProbeReturn MainWindow::tiler_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data)
{
    GstBuffer *buf = (GstBuffer *) info->data;
    guint num_rects = 0;
    NvDsObjectMeta *obj_meta = NULL;
    guint vehicle_count = 0;
    guint person_count = 0;
    NvDsMetaList * l_frame = NULL;
    NvDsMetaList * l_obj = NULL;
    NvDsDisplayMeta *display_meta = NULL;
     NvDecoderMeta * decoder_meta = NULL;
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
    NvDsMetaList * l_user_meta = NULL;
    NvDsUserMeta *user_meta = NULL;

    for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
      l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) (l_frame->data);
        //int offset = 0;
        for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
                l_obj = l_obj->next) {
            obj_meta = (NvDsObjectMeta *) (l_obj->data);
//            if (obj_meta->class_id == PGIE_CLASS_ID_VEHICLE) {
//                vehicle_count++;
//                num_rects++;
//            }
//            if (obj_meta->class_id == PGIE_CLASS_ID_PERSON) {
//                person_count++;
//                num_rects++;
//            }

                        rectL = obj_meta->rect_params.left;

                        rectT = obj_meta->rect_params.top;

                         rectW = obj_meta->rect_params.width;
                rectH = obj_meta->rect_params.height;

            for (l_user_meta = obj_meta->obj_user_meta_list; l_user_meta != NULL;
                l_user_meta = l_user_meta->next) {
              user_meta = (NvDsUserMeta *) (l_user_meta->data);
             // user_meta_data = (gchar *)user_meta->user_meta_data;

             // if(user_meta->base_meta.meta_type == NVDS_USER_FRAME_META_EXAMPLE)
             // {
                  decoder_meta = (NvDecoderMeta *)user_meta->user_meta_data;


               g_print("Dec Meta retrieved as NVDS USER METADTA For Frame_Num = %d Cat value= %c \n",
                        decoder_meta->frame_num, decoder_meta->cat);
                    g_print("frame type = %d, frame_num = %d decode_error_status = %d\n\n",
                        decoder_meta->frame_type, decoder_meta->frame_num,
                        decoder_meta->dec_err);
                    std::string patH = "/home/sigmind/Pictures/qtCrop/frame_" + std::to_string(imgNo) +  ".jpg";
                                cv::Mat received = decoder_meta->ass;
                                QString metaaa = " Balchal";
                                frameQueue.push_back(received.clone());
                               // DSaddFace_triggered(received, 5);
                              //  emit ui->emitDSFace(received, 5);

                               // reinterpret_cast<MainWindow*>(userData)->emitBlink();

                                //warkeaddFace_triggered(received, 5);
                              //  warker->doWark(received, metaaa, 2);
                              //  this->addFace_triggered(QPixmap, int);
                              //  cv::imwrite(patH, received);
                                received.release();
                                  imgNo++;

                g_print("\n");
              }


        }
          g_print ("Frame Number = %d Number of objects = %d "
            "Vehicle Count = %d Person Count = %d\n",
            frame_meta->frame_num, num_rects, vehicle_count, person_count);
#if 0
        display_meta = nvds_acquire_display_meta_from_pool(batch_meta);
        NvOSD_TextParams *txt_params  = &display_meta->text_params;
        txt_params->display_text = g_malloc0 (MAX_DISPLAY_LEN);
        offset = snprintf(txt_params->display_text, MAX_DISPLAY_LEN, "Person = %d ", person_count);
        offset = snprintf(txt_params->display_text + offset , MAX_DISPLAY_LEN, "Vehicle = %d ", vehicle_count);

        /* Now set the offsets where the string should appear */
        txt_params->x_offset = 10;
        txt_params->y_offset = 12;

        /* Font , font-color and font-size */
        txt_params->font_params.font_name = "Serif";
        txt_params->font_params.font_size = 10;
        txt_params->font_params.font_color.red = 1.0;
        txt_params->font_params.font_color.green = 1.0;
        txt_params->font_params.font_color.blue = 1.0;
        txt_params->font_params.font_color.alpha = 1.0;

        /* Text background color */
        txt_params->set_bg_clr = 1;
        txt_params->text_bg_clr.red = 0.0;
        txt_params->text_bg_clr.green = 0.0;
        txt_params->text_bg_clr.blue = 0.0;
        txt_params->text_bg_clr.alpha = 1.0;

        nvds_add_display_meta_to_frame(frame_meta, display_meta);
#endif

    }
    return GST_PAD_PROBE_OK;
}

static gboolean
bus_call (GstBus * bus, GstMessage * msg, gpointer data)
{
  GMainLoop *loop = (GMainLoop *) data;
  switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;
    case GST_MESSAGE_WARNING:
    {
      gchar *debug;
      GError *error;
      gst_message_parse_warning (msg, &error, &debug);
      g_printerr ("WARNING from element %s: %s\n",
          GST_OBJECT_NAME (msg->src), error->message);
      g_free (debug);
      g_printerr ("Warning: %s\n", error->message);
      g_error_free (error);
      break;
    }
    case GST_MESSAGE_ERROR:
    {
      gchar *debug;
      GError *error;
      gst_message_parse_error (msg, &error, &debug);
      g_printerr ("ERROR from element %s: %s\n",
          GST_OBJECT_NAME (msg->src), error->message);
      if (debug)
        g_printerr ("Error details: %s\n", debug);
      g_free (debug);
      g_error_free (error);
      g_main_loop_quit (loop);
      break;
    }
//#ifndef PLATFORM_TEGRA
    case GST_MESSAGE_ELEMENT:
    {
      if (gst_nvmessage_is_stream_eos (msg)) {
        guint stream_id;
        if (gst_nvmessage_parse_stream_eos (msg, &stream_id)) {
          g_print ("Got EOS from stream %d\n", stream_id);
        }
      }
      break;
    }
//#endif
    default:
      break;
  }
  return TRUE;
}

static void
cb_newpad (GstElement * decodebin, GstPad * decoder_src_pad, gpointer data)
{
  g_print ("In cb_newpad\n");
  GstCaps *caps = gst_pad_get_current_caps (decoder_src_pad);
  const GstStructure *str = gst_caps_get_structure (caps, 0);
  const gchar *name = gst_structure_get_name (str);
  GstElement *source_bin = (GstElement *) data;
  GstCapsFeatures *features = gst_caps_get_features (caps, 0);

  /* Need to check if the pad created by the decodebin is for video and not
   * audio. */
  if (!strncmp (name, "video", 5)) {
    /* Link the decodebin pad only if decodebin has picked nvidia
     * decoder plugin nvdec_*. We do this by checking if the pad caps contain
     * NVMM memory features. */
    if (gst_caps_features_contains (features, GST_CAPS_FEATURES_NVMM)) {
      /* Get the source bin ghost pad */
      GstPad *bin_ghost_pad = gst_element_get_static_pad (source_bin, "src");
      if (!gst_ghost_pad_set_target (GST_GHOST_PAD (bin_ghost_pad),
              decoder_src_pad)) {
        g_printerr ("Failed to link decoder src pad to source bin ghost pad\n");
      }
      gst_object_unref (bin_ghost_pad);
    } else {
      g_printerr ("Error: Decodebin did not pick nvidia decoder plugin.\n");
    }
  }
}

static void
decodebin_child_added (GstChildProxy * child_proxy, GObject * object,
    gchar * name, gpointer user_data)
{
  g_print ("Decodebin child added: %s\n", name);
  if (g_strrstr (name, "decodebin") == name) {
    g_signal_connect (G_OBJECT (object), "child-added",
        G_CALLBACK (decodebin_child_added), user_data);
  }
  if (g_strstr_len (name, -1, "nvv4l2decoder") == name) {
    g_print ("Seting bufapi_version\n");
    g_object_set (object, "bufapi-version", TRUE, NULL);
  }
}

static GstElement *
create_source_bin (guint index, gchar * uri)
{
  GstElement *bin = NULL, *uri_decode_bin = NULL;
  gchar bin_name[16] = { };

  g_snprintf (bin_name, 15, "source-bin-%02d", index);
  /* Create a source GstBin to abstract this bin's content from the rest of the
   * pipeline */
  bin = gst_bin_new (bin_name);

  /* Source element for reading from the uri.
   * We will use decodebin and let it figure out the container format of the
   * stream and the codec and plug the appropriate demux and decode plugins. */
  uri_decode_bin = gst_element_factory_make ("uridecodebin", "uri-decode-bin");

  if (!bin || !uri_decode_bin) {
    g_printerr ("One element in source bin could not be created.\n");
    return NULL;
  }

  /* We set the input uri to the source element */
  g_object_set (G_OBJECT (uri_decode_bin), "uri", uri, NULL);

  /* Connect to the "pad-added" signal of the decodebin which generates a
   * callback once a new pad for raw data has beed created by the decodebin */
  g_signal_connect (G_OBJECT (uri_decode_bin), "pad-added",
      G_CALLBACK (cb_newpad), bin);
  g_signal_connect (G_OBJECT (uri_decode_bin), "child-added",
      G_CALLBACK (decodebin_child_added), bin);

  gst_bin_add (GST_BIN (bin), uri_decode_bin);

  /* We need to create a ghost pad for the source bin which will act as a proxy
   * for the video decoder src pad. The ghost pad will not have a target right
   * now. Once the decode bin creates the video decoder and generates the
   * cb_newpad callback, we will set the ghost pad target to the video decoder
   * src pad. */
  if (!gst_element_add_pad (bin, gst_ghost_pad_new_no_target ("src",
              GST_PAD_SRC))) {
    g_printerr ("Failed to add ghost pad in source bin\n");
    return NULL;
  }

  return bin;
}

void MainWindow::load_faces()
{
    qDebug()<<"inside load faces\n";

   // qDebug()<<myStyles::blackFolderRelative<<endl;
   // GetFilesInDirectory(blacklist_names, myStyles::blackFolderRelative.toStdString());
   // qDebug()<<"strings loaded\n";
   // blacklist_descriptors = load_template(blacklist_names,face_detector, blacklist_templates, sp,face_net);
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    QPixmap wcIcon("./.rsc/wc.png");
    ui->iconWC->setPixmap(wcIcon.scaledToHeight(60));
    styles.initializeValues();
    qDebug() << myStyles::objectSensitivityValue;
    qDebug() << myStyles::emailsTo;

     QString cam1 = "rtsp://admin:admin123@103.113.17.146:2400/cam/realmonitor?channel=1&subtype=0";

  //   QString cam1 = "rtsp://admin:admin123@103.113.17.146:2400/cam/realmonitor?channel=1&subtype=0";

     QString cam2 = "rtsp://admin:admin123@103.113.17.146:2500/cam/realmonitor?channel=1&subtype=0";

      QString cam3 = "rtsp://admin:admin123@192.168.1.221/cam/realmonitor?channel=1&subtype=0"; // Entry verifocal

      QString cam4 = "rtsp://admin:00125680Sigmind@192.168.1.223/cam/realmonitor?channel=1&subtype=0"; // Front PTZ
 //
      QString cam5 = "/home/sigmind/deepstream_sdk_v4.0_jetson/samples/streams/sample_720p.mp4"; // Garage

      QString cam6 = "rtsp://admin:00125680@192.168.1.224/cam/realmonitor?channel=1&subtype=0"; // Lift view

      QString cam7 = "rtsp://admin:00125680@192.168.1.229/cam/realmonitor?channel=1&subtype=0"; // 2nd floor entry

      QString cam8 = "0";

      QString camList[5];

//      QFile file("./files/cameraList.txt");
//      if(!file.open(QIODevice::ReadOnly)) {
//          //QMessageBox::information(0, "error", file.errorString());
//      }

//      QTextStream in(&file);
//      int camListI=0;
//      while(!in.atEnd()) {
//         camList[camListI] = in.readLine();
//            camListI++;
//      }

      //QString cam5 = camList[0];
     // QString cam9 = camList[1];


    //qDebug() << "CamList read >> " << cam5 << " and " << cam9 ;
   // running= false;
    this->setWindowTitle("WATCHCAM");
      this->setAttribute(Qt::WA_DeleteOnClose , true);
    darknet_mutex = new QMutex();

   // this->show();

    flowLayout= new FlowLayout(0,0,0);

//    newFeed= new Feed(cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//    newFeed->set_blacklist_descriptor(blacklist_descriptors);
//    feeds.push_back(newFeed);

// //   QString cam2 = "0";

//    connect(this, SIGNAL(emitCam(QString,int)), newFeed, SLOT(initializeCameraMain(QString,int)));
//   // emit emitCam(cam1,0);


//    flowLayout->addWidget(newFeed);

//    newFeed2= new Feed( cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//   // newFeed2->set_blacklist_descriptor(blacklist_descriptors);
//    feeds.push_back(newFeed2);

//    connect(this, SIGNAL(emitCam2(QString,int)), newFeed2, SLOT(initializeCameraMain(QString,int)));

//    connect(newFeed2, SIGNAL(emitFace(QPixmap, int)), this, SLOT(addFace_triggered(QPixmap, int)));
//    connect(newFeed2, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed2, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed2, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));




//      emit emitCam2(cam5,2);

//    flowLayout->addWidget(newFeed2);


//  //  QThread::sleep(30);

//    // ++++++++++++++++++++++++++++++++
//    newFeed3= new Feed( cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//   // newFeed3->set_blacklist_descriptor(blacklist_descriptors);
//     feeds.push_back(newFeed3);

//    connect(this, SIGNAL(emitCam3(QString,int)), newFeed3, SLOT(initializeCameraMain(QString,int)));



//    connect(newFeed3, SIGNAL(emitFace(QPixmap, int)), this, SLOT(addFace_triggered(QPixmap, int)));
//    connect(newFeed3, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed3, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed3, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));


//    emit emitCam3(cam5,1);

//    flowLayout->addWidget(newFeed3);

////    //  QThread::sleep(30);

////    //  +++++++++++++++++++++++++++++++++

////    // ++++++++++++++++++++++++++++++++
//    newFeed4= new Feed( cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//   // newFeed4->set_blacklist_descriptor(blacklist_descriptors);
//    feeds.push_back(newFeed4);

//    connect(this, SIGNAL(emitCam4(QString,int)), newFeed4, SLOT(initializeCameraMain(QString,int)));

//    connect(newFeed4, SIGNAL(emitFace(QPixmap, int)), this, SLOT(addFace_triggered(QPixmap, int)));
//    connect(newFeed4, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed4, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed4, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));


//    // emit emitCam4(cam5,0);

//    flowLayout->addWidget(newFeed4);

//    //  QThread::sleep(30);

//    //  +++++++++++++++++++++++++++++++++


//    // ++++++++++++++++++++++++++++++++
//    newFeed6= new Feed( cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//   // newFeed6->set_blacklist_descriptor(blacklist_descriptors);
//     feeds.push_back(newFeed6);

//    connect(this, SIGNAL(emitCam6(QString,int)), newFeed6, SLOT(initializeCameraMain(QString,int)));

//    connect(newFeed6, SIGNAL(emitFace(QPixmap, int)), this, SLOT(addFace_triggered(QPixmap, int)));
//    connect(newFeed6, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed6, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed6, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));


//      emit emitCam6(cam6,0);


//    flowLayout->addWidget(newFeed6);

//     // QThread::sleep(30);



//    //  +++++++++++++++++++++++++++++++++

//    // ++++++++++++++++++++++++++++++++
//    newFeed7= new Feed( cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
//   // newFeed7->set_blacklist_descriptor(blacklist_descriptors);

//     feeds.push_back(newFeed7);
//    connect(this, SIGNAL(emitCam7(QString,int)), newFeed7, SLOT(initializeCameraMain(QString,int)));


//    connect(newFeed7, SIGNAL(emitFace(QPixmap, int)), this, SLOT(addFace_triggered(QPixmap, int)));
//    connect(newFeed7, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed7, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed7, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));




//        emit emitCam7(cam3,1);

//    flowLayout->addWidget(newFeed7);

    //  QThread::sleep(30);



    //  +++++++++++++++++++++++++++++++++

    ui->scrollAreaWidgetContents->setLayout(flowLayout);

    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //gridLayout= new QGridLayout();
    searchOn = false;
    searchFOn = false;
    searchLPRon = false;

    connect(this, SIGNAL(emitDSFace(cv::Mat, int)), this, SLOT(DSaddFace_triggered(cv::Mat, int)));
//    connect(newFeed, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    connect(newFeed, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));






    connect(this, SIGNAL(notifyLPR(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));

    facesWindow = new Faces(this);
   // facesWindow->deleteLater();
   // facesWindow = nullptr;
    ui->colorCombo->addItems(myStyles::colors);
    ui->objectCombo->addItems(myStyles::objects);

    QMenuBar *rightBar = new QMenuBar(ui->menuBar);

    QAction *action = new QAction("Notifications", rightBar);
    rightBar->addAction(action);

    connect(action, SIGNAL(triggered(bool)), this, SLOT(notificationSLot(bool)));

    ui->menuBar->setCornerWidget(rightBar);

    nots= new notWidget(this);

    setNotPosition();
    nots->setVisible(false);
    notOn= false;

    emailController= new ServiceController(this);

    connect(emailController, SIGNAL(addANot(Notification*)), this, SLOT(addNotToBar(Notification*)));


    //manager = new QNetworkAccessManager(this);

   // connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    ui->startButton->setDisabled(false);  // True for Trial

    ui->menuBar->setDisabled(false);    // True for trial

     //  ui->actionFootage_analysis->setDisabled(true);
       ui->scrollArea->setDisabled(false);
//    eula *eulaDialog = new eula;
//    eulaDialog->setAttribute( Qt::WA_DeleteOnClose );
//    connect(eulaDialog, SIGNAL(agree()), this, SLOT(agreed()));
//    connect(eulaDialog, SIGNAL(disagree()), this, SLOT(disagreed()));
//    eulaDialog->show();

    this->setWindowTitle("WATCHCAM");
//    ui->pauseButton->setHidden(true);
//    ui->playButton->setHidden(true);
//    ui->nextButton->setHidden(true);
  this->show();
    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);

    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));

  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), worker, SLOT(doWork(QPixmap,QString,int)));
   //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
      connect(worker, SIGNAL(valueChanged(QPixmap,QString,int)), this, SLOT(addLP(QPixmap,QString,int)));
    connect(worker, SIGNAL(finishedLPR()), thread, SLOT(quit()), Qt::DirectConnection);



    FRthread = new QThread();
    warker = new Warker();

    warker->moveToThread(FRthread);

     warker->load_template();

   // face_detector = dlib::get_frontal_face_detector();
    qDebug()<<"face detector initiated\n";
   // std::vector<string> names;
          //  GetFilesInDirectory(templates_names,"./faces/temp_late");


  //  warker->setup(templates_names, template_descriptors);
  //   warker->setup(templates_names,template_descriptors);
   // connect(this,SIGNAL(load_template()), warker, SLOT(receive_template()));

    connect(warker, SIGNAL(warkRequested()), FRthread, SLOT(start()));

  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    connect(this, SIGNAL(requestUpdateFR(cv::Mat,QString,int)), warker, SLOT(doWark(cv::Mat,QString,int)));

   //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
      connect(warker, SIGNAL(valueFRChanged(QPixmap,QString,int)), this, SLOT(addFR(QPixmap,QString,int)));
    connect(warker, SIGNAL(finishedFR()), FRthread, SLOT(quit()), Qt::DirectConnection);

    //  facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);


    trialTimer= new QTimer(this);
    connect(trialTimer, SIGNAL(timeout()), this, SLOT(cleanTiles()));
    trialTimer->start(3600000);


    // Deadly Hack Injection

    GMainLoop *loop = NULL;
      GstElement *pipeline = NULL, *streammux = NULL, *sink = NULL, *pgie = NULL,
          *nvvidconv = NULL, *nvosd = NULL, *tiler = NULL, *dsExample;
   // #ifdef PLATFORM_TEGRA
      GstElement *transform = NULL;
  //  #endif
      GstBus *bus = NULL;
      guint bus_watch_id;
      GstPad *tiler_src_pad = NULL;
      guint i, num_sources;
      guint tiler_rows, tiler_columns;
      guint pgie_batch_size;

    //  gchar videos[4][100] = {"file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4"}

//      gchar *videos = (gchar*)g_malloc0(4);
//        videos[0] = "file:///home/sigmind/sample_10-normal.mp4";

//      QString newVid = "file:///home/sigmind/sample_10-normal.mp4";
//      QByteArray ba;
//      ba = newVid.toUtf8();
//      gchar* videos = ba.constData();

        gboolean fullFrame = FALSE;

      /* Check input arguments */

      num_sources =  1;

      /* Standard GStreamer initialization */
      gst_init (0, NULL);
      loop = g_main_loop_new (NULL, FALSE);

      /* Create gstreamer elements */
      /* Create Pipeline element that will form a connection of other elements */
      pipeline = gst_pipeline_new ("dstest3-pipeline");

      /* Create nvstreammux instance to form batches from one or more sources. */
      streammux = gst_element_factory_make ("nvstreammux", "stream-muxer");

      if (!pipeline || !streammux) {
        g_printerr ("One element could not be created. Exiting.\n");
        //return -1;
      }
      gst_bin_add (GST_BIN (pipeline), streammux);

      gchar* videos[] = {"file:///home/sigmind/shyamoli-face.mp4","file:///home/sigmind/shyamoli-face.mp4", NULL} ;


      for (i = 0; i < num_sources; i++) {
        GstPad *sinkpad, *srcpad;
        gchar pad_name[16] = { };


        GstElement *source_bin = create_source_bin (i, videos[i]);

        if (!source_bin) {
          g_printerr ("Failed to create source bin. Exiting.\n");
        //  return -1;
        }

        gst_bin_add (GST_BIN (pipeline), source_bin);

        g_snprintf (pad_name, 15, "sink_%u", i);
        sinkpad = gst_element_get_request_pad (streammux, pad_name);
        if (!sinkpad) {
          g_printerr ("Streammux request sink pad failed. Exiting.\n");
         // return -1;
        }

        srcpad = gst_element_get_static_pad (source_bin, "src");
        if (!srcpad) {
          g_printerr ("Failed to get src pad of source bin. Exiting.\n");
         // return -1;
        }

        if (gst_pad_link (srcpad, sinkpad) != GST_PAD_LINK_OK) {
          g_printerr ("Failed to link source bin to stream muxer. Exiting.\n");
        //  return -1;
        }

        gst_object_unref (srcpad);
        gst_object_unref (sinkpad);
      }

      /* Use nvinfer to infer on batched frame. */
      pgie = gst_element_factory_make ("nvinfer", "primary-nvinference-engine");

      /* Use nvtiler to composite the batched frames into a 2D tiled array based
       * on the source of the frames. */
      tiler = gst_element_factory_make ("nvmultistreamtiler", "nvtiler");

      /* Use convertor to convert from NV12 to RGBA as required by nvosd */
      nvvidconv = gst_element_factory_make ("nvvideoconvert", "nvvideo-converter");

      /* Create OSD to draw on the converted RGBA buffer */
      nvosd = gst_element_factory_make ("nvdsosd", "nv-onscreendisplay");

     dsExample = gst_element_factory_make ("dsexample", "deepstream-example");

      /* Finally render the osd output */
    //#ifdef PLATFORM_TEGRA
    //  transform = gst_element_factory_make ("nvegltransform", "nvegl-transform");
      transform = gst_element_factory_make ("queue", "queue");
    //#endif
      //sink = gst_element_factory_make ("nveglglessink", "nvvideo-renderer");

      sink = gst_element_factory_make ("nvoverlaysink", "nvvideo-renderer");

      if (!pgie || !tiler || !nvvidconv || !nvosd || !sink) {
        g_printerr ("One element could not be created. Exiting.\n");
      //  return -1;
      }

    //#ifdef PLATFORM_TEGRA
      if(!transform) {
        g_printerr ("One tegra element could not be created. Exiting.\n");
      //  return -1;
      }
    //#endif
     g_object_set (G_OBJECT(sink), "sync", FALSE, NULL);
// overlay-x=0 overlay-y=0 overlay-w=1280 overlay-h=720 overlay=1
     g_object_set (G_OBJECT (dsExample),
             "full-frame", fullFrame, NULL);

     g_object_set(G_OBJECT(sink), "overlay-x", 50, "overlay-y", 50, "overlay-w", 640, "overlay-h", 480, "overlay", 1, NULL);

      g_object_set (G_OBJECT (streammux), "width", MUXER_OUTPUT_WIDTH, "height",
          MUXER_OUTPUT_HEIGHT, "batch-size", num_sources,
          "batched-push-timeout", MUXER_BATCH_TIMEOUT_USEC, NULL);

      /* Configure the nvinfer element using the nvinfer config file. */
      g_object_set (G_OBJECT (pgie),
          "config-file-path", "/home/sigmind/redaction_with_deepstream/configs/pgie_config_fd_lpd.txt", NULL);

      /* Override the batch-size set in the config file with the number of sources. */
      g_object_get (G_OBJECT (pgie), "batch-size", &pgie_batch_size, NULL);
      if (pgie_batch_size != num_sources) {
        g_printerr
            ("WARNING: Overriding infer-config batch-size (%d) with number of sources (%d)\n",
            pgie_batch_size, num_sources);
        g_object_set (G_OBJECT (pgie), "batch-size", num_sources, NULL);
      }

      tiler_rows = (guint) sqrt (num_sources);
      tiler_columns = (guint) ceil (1.0 * num_sources / tiler_rows);
      /* we set the tiler properties here */
      g_object_set (G_OBJECT (tiler), "rows", tiler_rows, "columns", tiler_columns,
          "width", TILED_OUTPUT_WIDTH, "height", TILED_OUTPUT_HEIGHT, NULL);

      /* we add a message handler */
      bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
      bus_watch_id = gst_bus_add_watch (bus, bus_call, loop);
      gst_object_unref (bus);

      /* Set up the pipeline */
      /* we add all elements into the pipeline */
   // #ifdef PLATFORM_TEGRA
      gst_bin_add_many (GST_BIN (pipeline), pgie, tiler, nvvidconv, dsExample, nvosd, transform, sink,
          NULL);
      /* we link the elements together
       * nvstreammux -> nvinfer -> nvtiler -> nvvidconv -> nvosd -> video-renderer */
      if (!gst_element_link_many (streammux, pgie, tiler, nvvidconv, dsExample, nvosd, transform, sink,
              NULL)) {
        g_printerr ("Elements could not be linked. Exiting.\n");
      //  return -1;
      }
//    #else
//    gst_bin_add_many (GST_BIN (pipeline), pgie, tiler, nvvidconv, nvosd, sink,
//          NULL);
//      /* we link the elements together
//       * nvstreammux -> nvinfer -> nvtiler -> nvvidconv -> nvosd -> video-renderer */
//      if (!gst_element_link_many (streammux, pgie, tiler, nvvidconv, nvosd, sink,
//              NULL)) {
//        g_printerr ("Elements could not be linked. Exiting.\n");
//        return -1;
//      }
//    #endif

      /* Lets add probe to get informed of the meta data generated, we add probe to
       * the sink pad of the osd element, since by that time, the buffer would have
       * had got all the metadata. */
      tiler_src_pad = gst_element_get_static_pad (nvosd, "src");
      if (!tiler_src_pad)
        g_print ("Unable to get src pad\n");
      else
        gst_pad_add_probe (tiler_src_pad, GST_PAD_PROBE_TYPE_BUFFER,
            tiler_src_pad_buffer_probe, NULL, NULL);



      /* Set the pipeline to "playing" state */
//      g_print ("Now playing:");
//      for (i = 0; i < num_sources; i++) {
//        g_print (" %s,", argv[i + 1]);
//      }
      g_print ("\n");
      gst_element_set_state (pipeline, GST_STATE_PLAYING);

      /* Wait till pipeline encounters an error or EOS */
      g_print ("Running...\n");
    //  g_main_loop_run (loop);
      while(1) {
      g_main_iteration(false);
      if (frameQueue.size() > 0) {
                      qDebug() << " Frame size CV  ............ shuvom";

                    cv::Mat frameSinK = frameQueue.front();
                   // cv::cvtColor(srcRgba , src , CV_RGBA2RGB);
                    emit emitDSFace(frameSinK, 5);

                    //cv::imwrite(patH, frameSinK);
                    frameSinK.release();
                    frameQueue.clear();
                    //imNo++;
      }


      }
      /* Out of the main loop, clean up nicely */
      g_print ("Returned, stopping playback\n");
      gst_element_set_state (pipeline, GST_STATE_NULL);
      g_print ("Deleting pipeline\n");
      gst_object_unref (GST_OBJECT (pipeline));
      g_source_remove (bus_watch_id);
      g_main_loop_unref (loop);



}



//void MainWindow::emitBlink(cv::Mat received) { // Should of course also be added in header.
//    emitDSFace(received, 5);
//}

MainWindow::~MainWindow()
{
    worker->abort();
    thread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete thread;
    delete worker;

    warker->abort();
    FRthread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete FRthread;
    delete warker;
   // delete newFeed2;
   // delete newFeed3;
    //delete newFeed4;

    delete ui;
}



void MainWindow::setSearchFaceOn()
{
    ui->searchFaceButton->setStyleSheet(myStyles::searchOn);
}

void MainWindow::setSearchObjectOn()
{
  //  ui->searchFaceButton->setStyleSheet(myStyles::defaultStyle);
    ui->searchObjectButton->setText("Searching");
}

void MainWindow::setSearchFaceOff()
{
  //  ui->searchObjectButton->setStyleSheet(myStyles::searchOn);
    ui->searchObjectButton->setText("Search OFF");
}

void MainWindow::setSearchObjectOff()
{
     ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
}

void MainWindow::on_searchFaceButton_clicked()
{
    QString tempF = ui->faceLineEdit->text();

   //  ui->startButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);")
    searchFOn = !searchFOn;
    if(searchFOn)
    {
   // setSearchObjectOn();
    ui->searchFaceButton->setText("Searching Face ...");
   //ui->searchObjectButton->setT;
   // this->setStyleSheet("MainWindow{background-color:green}");
    ui->searchFaceButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");
    }
    else
    {
       // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
       // setSearchObjectOff();
        ui->searchFaceButton->setText("Search Face OFF");
      //  this->setStyleSheet("MainWindow{background-color:red}");
        ui->searchFaceButton->setStyleSheet("background-color: rgb(0, 0, 0);");
       // found = false;
    }

    for(int i=0; i<feeds.size(); i++)
    {
        feeds[i]->search_requested(tempF,-1,"");
    }








}

void MainWindow::on_searchLPRbutton_clicked()
{
LPR = ui->LPRlineEdit->text();
    QString srch = ">>>>>>>>> Search LPR requested <<<<<<<<<<";
    qDebug(qUtf8Printable(srch));
    qDebug(qUtf8Printable(LPR));
    searchLPRon = !searchLPRon;
    if(searchLPRon)
    {
   // setSearchObjectOn();
  //  ui->searchFaceButton->setText("Searching Face ...");
   //ui->searchObjectButton->setT;
   // this->setStyleSheet("MainWindow{background-color:green}");
    ui->searchLPRbutton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");


    }
    else
    {
       // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
       // setSearchObjectOff();
       // ui->searchFaceButton->setText("Search Face OFF");
      //  this->setStyleSheet("MainWindow{background-color:red}");
        ui->searchLPRbutton->setStyleSheet("background-color: rgb(0, 0, 0);");
       // found = false;
        QString fuck = "fcuk";
        LPR = fuck;
    }



}

void MainWindow::on_searchObjectButton_clicked()
{
    QString object = myStyles::objects.at(ui->objectCombo->currentIndex()-1);
    int color = myStyles::colorValues.at(ui->colorCombo->currentIndex()-1);

    QString srch = ">>>>>>>>> Search requested <<<<<<<<<<";
    qDebug(qUtf8Printable(srch));
    qDebug(qUtf8Printable(object));
    qDebug(qUtf8Printable(QString::number(color)));

    searchOn = !searchOn;
    if(searchOn)
    {
   // setSearchObjectOn();
    ui->searchObjectButton->setText("Searching ...");
   //ui->searchObjectButton->setT;
   // this->setStyleSheet("MainWindow{background-color:green}");
    ui->searchObjectButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");





    }

    else
    {
       // ui->searchObjectButton->setStyleSheet(myStyles::defaultStyle);
       // setSearchObjectOff();
        ui->searchObjectButton->setText("Search OFF");
      //  this->setStyleSheet("MainWindow{background-color:red}");
        ui->searchObjectButton->setStyleSheet("background-color: rgb(0, 0, 0);");
       // found = false;
    }

    for(int i=0; i<feeds.size(); i++)
    {
        feeds[i]->search_requested("",color,object);
    }

}
void MainWindow::on_startButton_pressed()
{
    if(!running){

//        manager->get(QNetworkRequest(QUrl("http://www.sigmindai.net/wc-surv/wc-surv.php?passkey=secret-wc")));

//        ui->startButton->setText("Checking..");
//        ui->startButton->setStyleSheet("background-color: rgb(170, 255, 127);");
//        //start camera

////        cam = new Camera(ui->linkLine->text().toStdString().c_str());
////        cam->moveToThread(thread);

////        connect(cam, SIGNAL(ui_go(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)), this,
////                SLOT(update_ui(cv::Mat, cv::Mat, std::vector< watchcam::rectangle >)));
////        connect(cam, SIGNAL(start_requested()), thread, SLOT(start()));
////        connect(thread, SIGNAL(started()), cam, SLOT(go()));
////        cam->start();

//        ui->menuBar->setDisabled(false);
//       // ui->actionFootage_analysis->setDisabled(false);
//        ui->scrollArea->setDisabled(false);
        running = true;

    }
    else {
        ui->startButton->setText("Invalid");

       // ui->startButton->setDisabled(true);

        //close camera
      //  ui->menuBar->setDisabled(true);   // Uncomment for trial
       // ui->actionFootage_analysis->setDisabled(true);
     //   ui->scrollArea->setDisabled(true);  // Uncomment for trial
        running = false;
    }
}

void MainWindow::notificationSLot(bool)
{
    if(!notOn){
        nots->setVisible(true);
        notOn= true;
    }
    else {
        nots->setVisible(false);
        notOn= false;
    }
}

void MainWindow::makeNotification(QPixmap pic, QString name, int cam)
{
   // faceNo++;
    Notification *newNoti= new Notification(name, "", QString::number(cam), pic.scaledToHeight(140));
    emailController->addNot(newNoti);
}

void MainWindow::addNotToBar(Notification *noti)
{
    Not *newNot= new Not(noti->pic, noti->name, noti->cam, "", this);
    nots->addNot(newNot);
    nots->setVisible(true);
    notOn= true;
}

void MainWindow::setNotPosition()
{
    int y= ui->menuBar->geometry().y();//+ 20;
     //   int y= this->height()-980;
    int x= this->width()-402;
    nots->move(x,y);
    nots->setFixedWidth(400);
    nots->setFixedHeight(600);
}

int MainWindow::widthCal()
{
    //qDebug() << flowLayout->geometry().width();
    int rem = (flowLayout->geometry().width())%(myStyles::minWidth);
    int res = (flowLayout->geometry().width())/(myStyles::minWidth);
    if(rem)
    {
        //qDebug() << "hey " << (res+1);
        return (flowLayout->geometry().width()-1)/(res+1);
    }
    else
    {
        //qDebug() << "res" << res;
        return (myStyles::minWidth-1);
    }
}

void MainWindow::setSizes(int width)
{
    int height= (width*9)/16;
    myStyles::runningFeedWidth = width;
    myStyles::runningFeedHeight = height;

    //qDebug() << "inside sizes " << width;
    for(int i=0;i<feeds.size();i++){
        feeds[i]->setSizes(width, height);
    }
}

void MainWindow::on_actionAdd_Camera_triggered()
{
    Feed *newFeed= new Feed(cam_count++,myStyles::runningFeedWidth,myStyles::runningFeedHeight, darknet_mutex, templates_names, template_descriptors, this);
    newFeed->set_blacklist_descriptor(blacklist_descriptors);

    feeds.push_back(newFeed);
    connect(newFeed, SIGNAL(emitFace(QPixmap , QString, int)), this, SLOT(addFace_triggered(QPixmap,QString,int)));
    connect(newFeed, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
    connect(newFeed, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    connect(newFeed, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));

     //flowLayout->addWidget(newFeed);
    flowLayout->addWidget(newFeed);

    //qDebug() << ui->scrollAreaWidgetContents->geometry().height() << endl;

    setSizes(widthCal());
    thread = new QThread();
    worker = new Worker();

    worker->moveToThread(thread);

    connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));

  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), worker, SLOT(doWork(QPixmap,QString,int)));
    connect(worker, SIGNAL(valueChanged(QPixmap,QString,int)), this, SLOT(addLP(QPixmap,QString,int)));
    connect(worker, SIGNAL(finishedLPR()), thread, SLOT(quit()), Qt::DirectConnection);


    FRthread = new QThread();
    warker = new Warker();

    warker->moveToThread(FRthread);
   // warker->setup(templates_names, template_descriptors);
  //  connect(this,SIGNAL(load_template()), warker, SLOT(receive_template()));

   //  load_faces();
    connect(warker, SIGNAL(warkRequested()), FRthread, SLOT(start()));

  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
    connect(this, SIGNAL(requestUpdateFR(cv::Mat,QString,int)), warker, SLOT(doWark(cv::Mat,QString,int)));
   //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
      connect(warker, SIGNAL(valueFRChanged(QPixmap,QString,int,matrix<float,0,1>)), this, SLOT(addFR(QPixmap,QString,int,matrix<float,0,1>)));
    connect(warker, SIGNAL(finishedFR()), FRthread, SLOT(quit()), Qt::DirectConnection);


}

void MainWindow::replyFinished(QNetworkReply *rep){
    if(rep->readAll() == "ok") {
//        qDebug() << "valid";

//        trialTimer= new QTimer(this);
//        connect(trialTimer, SIGNAL(timeout()), this, SLOT(trialCheck()));
//        trialTimer->start(300000);

//        manager = new QNetworkAccessManager(this);

//        connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinishedOnline(QNetworkReply*)));
    }
    else {
//        qDebug() << rep->readAll();
//        qDebug() << "error trial starting";
//       ui->startButton->setDisabled(true);
//        expireDialog *expire = new expireDialog;
//        expire->setAttribute( Qt::WA_DeleteOnClose );   // Uncomment for trial
//        expire->show();
//        this->close();
    }


}

void MainWindow::replyFinishedOnline(QNetworkReply *rep){
    if(rep->readAll() == "ok") {
//        qDebug() << "valid";

    }

    else {
//        trialTimer->stop();
//        ui->startButton->setDisabled(false);
//        expireDialog *expire = new expireDialog;
//        expire->setAttribute( Qt::WA_DeleteOnClose );
//        expire->show();

//        this->close();
    }


}

void MainWindow::trialCheck(){
   // manager->get(QNetworkRequest(QUrl("http://www.sigmindai.net/wc-surv/wc-surv.php?passkey=secret-wc")));
}

void MainWindow::disagreed(){
    ui->startButton->setDisabled(true);
    ui->actionAdd_Camera->setDisabled(true);
    ui->actionFootage_analysis->setDisabled(true);
    ui->scrollArea->setDisabled(true);
    this->close();
}

void MainWindow::agreed(){

    ui->startButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->actionAdd_Camera->setDisabled(false);
    ui->actionFootage_analysis->setDisabled(false);
    ui->scrollArea->setDisabled(false);
//ui->actionAdd_Camera->setDisabled(false);
  //  manager->get(QNetworkRequest(QUrl("http://www.sigmindai.net/wc-surv/wc-surv.php?passkey=secret-wc")));
}

void MainWindow::on_startButton_released()
{
    if(running){
        ui->startButton->setText("BHTPA-JT");
        ui->startButton->setStyleSheet("background-color: rgba(255, 0, 0, 150);");

        ui->startButton->setDisabled(false);
    }
    else{
        ui->startButton->setText("Check");
        ui->startButton->setStyleSheet("background-color: rgb(170, 255, 127);");
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    setSizes(widthCal());
    setNotPosition();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(notOn){
        if(!nots->geometry().contains(event->pos())) {
            nots->setVisible(false);
            notOn=false;
        }
    }
}

void MainWindow::on_actionShow_Faces_triggered()
{
       facesWindow = new Faces(this);
        facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    facesWindow->show();

}

void MainWindow::on_actionAdd_face_triggered()
{

    //facesWindow->show();
}

void MainWindow::addFace_triggered(cv::Mat pic, int indx)
{
     QString enc = "receive Face";

//       facesWindow->addFR(pic, enc, indx);


    warker->requestWark();

    emit requestUpdateFR(pic, enc, indx);

}

void MainWindow::DSaddFace_triggered(cv::Mat pic, int indx)
{
     QString enc = "receive Face";

//       facesWindow->addFR(pic, enc, indx);


    warker->requestWark();

    emit requestUpdateFR(pic, enc, indx);

}





void MainWindow::addLPR_triggered(QPixmap pic, int indx)
{
   // worker->abort();
    //thread->wait(); // If the thread is not running, this will immediately return.
    QString enc = "receive tileLP";
    worker->requestWork();

    emit requestUpdateLPR(pic, enc, indx);
  // QString trig = "Add LPR triggered";
  // facesWindow->addLPR(pic, trig, indx);
}

void MainWindow::addFR(QPixmap pic, QString str, int indx)
{
    std::string faceData = str.toStdString();
        std::string susu = "sush";
//    if(faceData.find(susu) != std::string::npos) {
//        //makeNotification(pic, qstr, indx);
//        emit notifyLPR(pic, str, indx);
//    }
//    else
//    {
          // QString baal = " bal amar";

       // facesWindow->addUniqueFace(pic,str,indx,face_descriptor);

     //  if(indx) {
           emit notifyLPR(pic, str, indx);
    //}
  //  facesWindow->addFR(pic, str, indx);
        facesWindow->addFaceRecognized(pic, str, indx);// }

}


void MainWindow::addLP(QPixmap pic, QString str, int indx)
{
    QString trig = "Add LPR triggered";
    std::stringstream plateStream;
          std::wstring plateID = str.toStdWString().c_str();
           int i=0;



           for (auto &letter : plateID) {
               if (letter == L'৮') {

                          plateStream << "8";
                      }
                      else if (letter == L'৩') {

                          plateStream << "3";
                      }
                       else if (letter == L'৭') {

                          plateStream << "7";
                      }
                        else if (letter == L'৭') {

                          plateStream << "7";
                      }
                        else if (letter == L'৬') {

                          plateStream << "6";
                      }
                        else if (letter == L'৯') {

                          plateStream << "9";
                      }
                        else if (letter == L'৫') {

                          plateStream << "5";
                      }
                         else if (letter == L'৪') {

                          plateStream << "4";
                      }
                         else if (letter == L'২') {

                          plateStream << "2";
                      }
                         else if (letter == L'১') {

                          plateStream << "1";
                      }
                         else if (letter == L'০') {

                          plateStream << "0";
                      }


                         else if (letter == L'ক') {

                        plateStream << "Ka-";
                      }
                         else if (letter == L'ঢ') {

                        plateStream << "Dha";
                      }
               else if (letter == L'ম') {

              plateStream << "Me";
            }
               else if (letter == L'ট') {

              plateStream << "Tro-";
            }
               i++;
           }
           std::string plateData = plateStream.str();
           QString lpr_path = "./captures/license_plates/";
           QString qstr = QString::fromStdString(plateData);
           QFile file(lpr_path+qstr);
           file.open(QIODevice::WriteOnly);
           pic.save(&file, "PNG");

           std::string plateRequest = LPR.toUtf8().constData();

//           if(plateData.find(plateRequest) != std::string::npos) {
//               //makeNotification(pic, qstr, indx);
//               emit notifyLPR(pic, qstr, indx);
//           }
    //facesWindow->addObject(pic, str, indx);
    facesWindow->addLPR(pic, str, indx);


}
void MainWindow::addObject(QPixmap pic, QString str, int indx)
{

    facesWindow->addObject(pic, str, indx);
}

void MainWindow::on_actionTracking_triggered()
{
    trackingWindow = new trackingSettingsDialog(this);
    trackingWindow->show();

}

void MainWindow::on_tileButton_clicked()
{
//    facesWindow = new Faces(this);
//     facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
    facesWindow->show();

}



void MainWindow::on_actionSettings_triggered()
{
    settingsDialog *newSettings= new settingsDialog(this);
    connect(newSettings, SIGNAL(objectSensitivityChanged()), this, SLOT(setObjectThreshold()));
    newSettings->exec();
}

void MainWindow::setObjectThreshold()
{
    for(int i=0;i<feeds.size();i++){
        feeds[i]->reset_object_threshold();
    }
}

void MainWindow::on_actionRTSS_triggered()
{
 //facesWindow->deleteLater();
}

//void MainWindow::on_actionFootage_analysis_triggered()
//{
//    footage= new footageWindow(this);
//    footage->par_mutex = darknet_mutex;
//    footage->setAttribute( Qt::WA_DeleteOnClose );
//    footage->show();
//}
void MainWindow::on_actionAbout_2_triggered()
{
    aboutDialog *about = new aboutDialog(this);
    about->setAttribute( Qt::WA_DeleteOnClose );
    about->show();
}
//void valueChanged(QPixmap p, QString str, int indx)
//{
//   // emit valueChangedALL(p, str,indx);
//}
void MainWindow::cleanTiles()
{
trialTimer->stop();
    if (facesWindow != nullptr)
       {
        facesWindow->deleteLater();
          // delete facesWindow;
        facesWindow = new Faces(this);
         trialTimer->start(3600000);
        // facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
       }
}
