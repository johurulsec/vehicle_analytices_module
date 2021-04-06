#include "deepstream_source_code.h"

#include <QDebug>
#include <QFile>
#include <QMutex>
#include "deepstream/deepstream_app.h"
#include "deepstream_config_file_parser.h"
#include "nvds_version.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "deepstream/deepstream_app.h"
#include "deepstream_config_file_parser.h"
#include "nvds_version.h"
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <gst/gst.h>
#include <glib.h>
#include "gstnvdsmeta.h"
#include <ostream>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <deque>


#define MAX_INSTANCES 128
#define APP_TITLE "WatchCam"

#define DEFAULT_X_WINDOW_WIDTH 1920
#define DEFAULT_X_WINDOW_HEIGHT 1080
#define MAX_INSTANCES 128
#define APP_TITLE "WATCHCAM"
#define CHECK_ERROR(error)

#define PGIE_CLASS_ID_VEHICLE 0
#define PGIE_CLASS_ID_PERSON 2

#define MAX_DISPLAY_LEN 64

#define CONFIG_GROUP_APP "application"
#define CONFIG_GROUP_APP_ENABLE_PERF_MEASUREMENT "enable-perf-measurement"
#define CONFIG_GROUP_APP_PERF_MEASUREMENT_INTERVAL "perf-measurement-interval-sec"
#define CONFIG_GROUP_APP_GIE_OUTPUT_DIR "gie-kitti-output-dir"
#define CONFIG_GROUP_APP_GIE_TRACK_OUTPUT_DIR "kitti-track-output-dir"

#define CONFIG_GROUP_TESTS "tests"
#define CONFIG_GROUP_TESTS_FILE_LOOP "file-loop"

GST_DEBUG_CATEGORY_EXTERN (APP_CFG_PARSER_CAT);

AppCtx *appCtx[MAX_INSTANCES];
static guint cintr = FALSE;
static GMainLoop *main_loop = NULL;
static gchar **cfg_files = NULL;
static gchar **input_files = NULL;
static gboolean print_version = FALSE;
static gboolean show_bbox_text = FALSE;
static gboolean print_dependencies_version = FALSE;
static gboolean quit = FALSE;
static gint return_value = 0;
static guint num_instances;
static guint num_input_files;
static GMutex fps_lock;
static gdouble fps[MAX_SOURCE_BINS];
static gdouble fps_avg[MAX_SOURCE_BINS];
static guint num_fps_inst = 0;

static Display *display = NULL;
static Window windows[MAX_INSTANCES] = { 0 };

static gint source_ids[MAX_INSTANCES];

static GThread *x_event_thread = NULL;
static GMutex disp_lock;
static guint demux_batch_num = 0;

GST_DEBUG_CATEGORY (NVDS_APP);

GOptionEntry entries[] = {
    {"version", 'v', 0, G_OPTION_ARG_NONE, &print_version,
     "Print DeepStreamSDK version", NULL}
    ,
    {"tiledtext", 't', 0, G_OPTION_ARG_NONE, &show_bbox_text,
     "Display Bounding box labels in tiled mode", NULL}
    ,
    {"version-all", 0, 0, G_OPTION_ARG_NONE, &print_dependencies_version,
     "Print DeepStreamSDK and dependencies version", NULL}
    ,
    {"cfg-file", 'c', 0, G_OPTION_ARG_FILENAME_ARRAY, &cfg_files,
     "Set the config file", NULL}
    ,
    {"input-file", 'i', 0, G_OPTION_ARG_FILENAME_ARRAY, &input_files,
     "Set the input file", NULL}
    ,
    {NULL}
    ,
};


static guint batch_num = 0;

GST_DEBUG_CATEGORY_EXTERN (NVDS_APP);

GQuark _dsmeta_quark;

#define CEIL(a,b) ((a + b - 1) / b)
#define SOURCE_RESET_INTERVAL_IN_MS 60000




/**
 * Function called at regular interval when one of NV_DS_SOURCE_RTSP type
 * source in the pipeline is down / disconnected. This function try to
 * reconnect the source by resetting that source pipeline.
 */

gchar pgie_classes_str[4][32] = { "Vehicle", "TwoWheeler", "Person",
                                  "RoadSign"
                                };
QMutex *g_mutex;
bool EOS = false;
//int imgNo;

int rectL, rectT, rectW, rectH;
#define FPS_PRINT_INTERVAL 300
//static struct timeval start_time = { };
std::deque<cv::Mat> frameQueue;

bool loop_off = FALSE;
NvDsSourceConfig global_source_config;
int imgNo=1;

typedef struct _NvDecoderMeta
{
    gchar cat;
    cv::Mat ass;
    guint frame_type;
    guint frame_num;
    gboolean dec_err;
} NvDecoderMeta;

//struct croppedFace{
//   //_croppedFace() {}
// char *message;
//Warker *warker;

//};

//struct croppedFace d;
int que=0;

//void Deepstream_source_code::draw_detections_with_FR(image im, image orig, int num, float thrsh, box *boxes, float **probs, char **names, image **alphabet, int classes,
//                                                     std::vector<watchcam::rectangle > &rects)
//{
//}

Deepstream_source_code::Deepstream_source_code(QObject *parent/*, int w, int h*/) : QObject(parent)
{
    //    this->wi = w;
    //    this->he = h;
}
void Deepstream_source_code::constructorDeepStream(){
    GOptionContext *ctx = NULL;
    GOptionGroup *group = NULL;
    GError *error = NULL;
    guint i;
    printf("defining arguments");
    gint myargc=3;
    char *array[] = {
        "./deepstream-appQT",
        "-c",
      //  "./.cfg/deepstream-app/source4_1080p_dec_infer-resnet_tracker_sgie_tiled_display_int8.txt",
        //   "/home/sigmind/Downloads/deepstream_sdk_v5.0.0_jetson/opt/nvidia/deepstream/deepstream-5.0/samples/configs/deepstream-app/source30_1080p_dec_infer-resnet_tiled_display_int8.txt",
        "./.cfg/deepstream-app/deepstream_app_source1_peoplenet.txt",
        NULL
    };

    char** myargv = array;


    ctx = g_option_context_new ("Nvidia DeepStream Demo");
    group = g_option_group_new ("abc", NULL, NULL, NULL, NULL);
    g_option_group_add_entries (group, entries);

    g_option_context_set_main_group (ctx, group);
    g_option_context_add_group (ctx, gst_init_get_option_group ());

    GST_DEBUG_CATEGORY_INIT (NVDS_APP, "NVDS_APP", 0, NULL);

    if (!g_option_context_parse (ctx, &myargc, &myargv, &error)) {
        NVGSTDS_ERR_MSG_V ("%s", error->message);
        // return -1;
    }

    if (print_version) {
        g_print ("deepstream-app version %d.%d.%d\n",
                 NVDS_APP_VERSION_MAJOR, NVDS_APP_VERSION_MINOR, NVDS_APP_VERSION_MICRO);
        nvds_version_print ();
        // return 0;
    }

    if (print_dependencies_version) {
        g_print ("deepstream-app version %d.%d.%d\n",
                 NVDS_APP_VERSION_MAJOR, NVDS_APP_VERSION_MINOR, NVDS_APP_VERSION_MICRO);
        nvds_version_print ();
        nvds_dependencies_version_print ();
        // return 0;
    }

    if (cfg_files) {
        num_instances = g_strv_length (cfg_files);
        g_print("Number of instances ------------ %d\n",num_instances);
    }
    if (input_files) {
        num_input_files = g_strv_length (input_files);
        g_print("Number of num_input_files ------------ %d\n",num_input_files);
    }

    memset (source_ids, -1, sizeof (source_ids));

    //  if (!cfg_files || num_instances == 0) {
    //    NVGSTDS_ERR_MSG_V ("Specify config file with -c option");
    //    return_value = -1;
    //    goto done;
    //  }

    for (i = 0; i < num_instances; i++) {
        appCtx[i] = (AppCtx *)g_malloc0 (sizeof (AppCtx));
        appCtx[i]->person_class_id = -1;
        appCtx[i]->car_class_id = -1;
        appCtx[i]->index = i;
        if (show_bbox_text) {
            appCtx[i]->show_bbox_text = TRUE;
        }

        if (input_files && input_files[i]) {
            appCtx[i]->config.multi_source_config[0].uri =
                    g_strdup_printf ("file://%s", input_files[i]);
            g_free (input_files[i]);
        }

        if (!parse_config_file (&appCtx[i]->config, cfg_files[i])) {
            NVGSTDS_ERR_MSG_V ("Failed to parse config file '%s'", cfg_files[i]);
            appCtx[i]->return_value = -1;
            //goto done;
        }
    }

    for (i = 0; i < num_instances; i++) {
        if (!create_pipeline (appCtx[i], NULL,
                              all_bbox_generated, perf_cb, overlay_graphics)) {
            NVGSTDS_ERR_MSG_V ("Failed to create pipeline");
            return_value = -1;
            //goto done;
        }
    }

    main_loop = g_main_loop_new (NULL, TRUE);

    //    GMainContext *context = g_main_context_default ();
    //      gboolean quit = FALSE;
    //     g_main_context_push_thread_default (context);

    //     while(1)
    //     {
    //         g_main_context_iteration (NULL, FALSE);
    //     }
    _intr_setup ();
    g_timeout_add (400, check_for_interrupt, NULL);


    g_mutex_init (&disp_lock);
    display = XOpenDisplay (NULL);
    g_print("befords");
    disToMain = display;
    MainWindow::dispInMainWind2();


    for (i = 0; i < num_instances; i++) {

        guint j;

        if (gst_element_set_state (appCtx[i]->pipeline.pipeline,
                                   GST_STATE_PAUSED) == GST_STATE_CHANGE_FAILURE) {
            NVGSTDS_ERR_MSG_V ("Failed to set pipeline to PAUSED");
            return_value = -1;
            //goto done;
        }

        if (!appCtx[i]->config.tiled_display_config.enable)
            continue;

        for (j = 0; j < appCtx[i]->config.num_sink_sub_bins; j++) {
            //g_print("num_instances = %d\n", num_instances);
            XTextProperty xproperty;
            gchar *title;
            guint width, height;

            if (!GST_IS_VIDEO_OVERLAY (appCtx[i]->pipeline.instance_bins[0].
                                       sink_bin.sub_bins[j].sink)) {
                continue;
            }

            if (!display) {
                NVGSTDS_ERR_MSG_V ("Could not open X Display");
                return_value = -1;
                //goto done;
            }

            if (appCtx[i]->config.sink_bin_sub_bin_config[j].render_config.width)
                width =
                        appCtx[i]->config.sink_bin_sub_bin_config[j].render_config.width;
            else
                width = appCtx[i]->config.tiled_display_config.width;

            if (appCtx[i]->config.sink_bin_sub_bin_config[j].render_config.height)
                height =
                        appCtx[i]->config.sink_bin_sub_bin_config[j].render_config.height;
            else
                height = appCtx[i]->config.tiled_display_config.height;

            width = (width) ? width : DEFAULT_X_WINDOW_WIDTH;
            height = (height) ? height : DEFAULT_X_WINDOW_HEIGHT;

            g_print("Width of mainWindow %d\n", MainWindow::getDispWidth());
            g_print("Height of mainWindow %d\n", MainWindow::getDispHeight());

            //            windows[i] =
            //                    XCreateSimpleWindow (display, RootWindow (display,
            //                                                              DefaultScreen (display)), 1000,1000, (MainWindow::getDispWidth()-MainWindow::getDispWidth()/3)+110, MainWindow::getDispHeight()/2, 2, 0x00000000,
            //                                         0x00000000);

            windows[i] =
                    XCreateSimpleWindow (display, RootWindow (display,
                                                              DefaultScreen (display)), 0, 0, MainWindow::getDispWidth()/2, MainWindow::getDispHeight()/2, 2, 0x00000000,
                                         0x00000000);
            ////qDebug() << "Another dis ddd" << MainWindow::getDispWidth()/2<<", "<<MainWindow::getDispHeight()/2;

            //            windows[i] =
            //                    XCreateSimpleWindow (display, RootWindow (display,
            //                                                              DefaultScreen (display)), 500, 500, 721, 461, 2, 0x00000000,
            //                                         0x00000000);
            //                        windows[i] =
            //                                XCreateSimpleWindow (display, RootWindow (display,
            //                                                                          DefaultScreen (display)), 600, 100, width, height-200, 2, 0x00000000,
            //                                                     0x00000000);

            singleWin = windows[i];
            MainWindow::dispInMainWind();
            g_print("afterds");


            if (num_instances > 1)
                title = g_strdup_printf (title, APP_TITLE "-%d", i);
            else
                title = g_strdup (APP_TITLE);
            if (XStringListToTextProperty ((char **) &title, 1, &xproperty) != 0) {
                XSetWMName (display, windows[i], &xproperty);
                XFree (xproperty.value);
            }

            XSetWindowAttributes attr = { 0 };
            if ((appCtx[i]->config.tiled_display_config.enable &&
                 appCtx[i]->config.tiled_display_config.rows *
                 appCtx[i]->config.tiled_display_config.columns == 1) ||
                    (appCtx[i]->config.tiled_display_config.enable == 0 &&
                     appCtx[i]->config.num_source_sub_bins == 1)) {
                attr.event_mask = KeyPress;
            } else {
                attr.event_mask = ButtonPress | KeyRelease;
            }
            XChangeWindowAttributes (display, windows[i], CWEventMask, &attr);

            Atom wmDeleteMessage = XInternAtom (display, "WM_DELETE_WINDOW", False);
            if (wmDeleteMessage != None) {
                XSetWMProtocols (display, windows[i], &wmDeleteMessage, 1);
            }

            //            XMapRaised (display, windows[i]);
            //            XSync (display, 1);

            gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (appCtx
                                                                    [i]->pipeline.instance_bins[0].sink_bin.sub_bins[j].sink),
                    (gulong) windows[i]);
            gst_video_overlay_expose (GST_VIDEO_OVERLAY (appCtx[i]->
                                                         pipeline.instance_bins[0].sink_bin.sub_bins[j].sink));
            if (!x_event_thread)
                x_event_thread = g_thread_new ("nvds-window-event-thread",
                                               nvds_x_event_thread, NULL);
        }
    }

    /* Dont try to set playing state if error is observed */
    if (return_value != -1) {
        for (i = 0; i < num_instances; i++) {
            if (gst_element_set_state (appCtx[i]->pipeline.pipeline,
                                       GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {

                g_print ("\ncan't set pipeline to playing state.\n");
                return_value = -1;
                //goto done;
            }
        }
    }

    print_runtime_commands ();



    changemode (1);

    g_timeout_add (40, event_thread_func, NULL);
    g_main_loop_run (main_loop);



    //return return_value;


    //..................end of deepstream_app_main.c......................

    // g_main_loop_run (main_loop);
    // GMainContext *context = g_main_context_default ();
    //  gboolean quit = FALSE;
    // g_main_context_push_thread_default (context);
    /* Set up the D-Bus connection to work in the GLib event loop. */
    //dbus_connection_setup_with_g_main (dbus_connection, context);

    /* Run the GLib event loop. */
    // while (!EOS) {

    //  if(!loop_off) {
    //   g_main_context_iteration (NULL, FALSE);

    //        cv::Mat frameSinK; //new comment
    // Working good

    //        if (frameQueue.size() > 0) {
    //            //qDebug() << " Frame size CV  ............ shuvom";

    //            cv::Mat frameSinK = frameQueue.front();

    //            if( frameSinK.empty())                      // Check for invalid input
    //            {
    //                std::cout <<  "Could not open or find the image :: frameSinK.empty()" << std::endl ;
    //            }
    //            else {
    //                // g_main_context_iteration(NULL, FALSE);
    //                //qDebug() << " Before Emit .....";
    //                //emit emitDSFace(frameSinK.clone(), 5);

    //                //
    //                //    g_object_set(G_OBJECT(sink), "overlay-x", 0, "overlay-y", 100, "overlay-w", 500, "overlay-h", 800, "overlay", 1, NULL);

    //                frameSinK.release();
    //                //qDebug() << " Frame Queue Cleared";

    //            }


    //            frameQueue.clear();
    //            //            frameSinK.release(); //new comment
    //        }
    // }
    changemode (0);

    //done:

    g_print ("Quitting\n");
    for (i = 0; i < num_instances; i++) {
        if (appCtx[i]->return_value == -1)
            return_value = -1;
        destroy_pipeline (appCtx[i]);

        g_mutex_lock (&disp_lock);
        if (windows[i])
            XDestroyWindow (display, windows[i]);
        windows[i] = 0;
        g_mutex_unlock (&disp_lock);

        g_free (appCtx[i]);
    }

    g_mutex_lock (&disp_lock);
    if (display)
        XCloseDisplay (display);
    display = NULL;
    g_mutex_unlock (&disp_lock);
    g_mutex_clear (&disp_lock);

    if (main_loop) {
        g_main_loop_unref (main_loop);
    }

    if (ctx) {
        g_option_context_free (ctx);
    }

    if (return_value == 0) {
        g_print ("App run successful\n");
    } else {
        g_print ("App run failed\n");
    }

    gst_deinit ();
}
void Deepstream_source_code::startDeepStream(){
    this->constructorDeepStream();
}

gboolean Deepstream_source_code::add_and_link_broker_sink(AppCtx *appCtx)
{
    NvDsConfig *config = &appCtx->config;
    /** Only first instance_bin broker sink
   * employed as there's only one analytics path for N sources
   * NOTE: There shall be only one [sink] group
   * with type=6 (NV_DS_SINK_MSG_CONV_BROKER)
   * a) Multiple of them does not make sense as we have only
   * one analytics pipe generating the data for broker sink
   * b) If Multiple broker sinks are configured by the user
   * in config file, only the first in the order of
   * appearance will be considered
   * and others shall be ignored
   * c) Ideally it should be documented (or obvious) that:
   * multiple [sink] groups with type=6 (NV_DS_SINK_MSG_CONV_BROKER)
   * is invalid
   */
    NvDsInstanceBin *instance_bin = &appCtx->pipeline.instance_bins[0];
    NvDsPipeline *pipeline = &appCtx->pipeline;

    for (guint i = 0; i < config->num_sink_sub_bins; i++) {
        if(config->sink_bin_sub_bin_config[i].type == NV_DS_SINK_MSG_CONV_BROKER)
        {
            if(!pipeline->common_elements.tee) {
                NVGSTDS_ERR_MSG_V ("%s failed; broker added without analytics; check config file\n", __func__);
                return FALSE;
            }
            /** add the broker sink bin to pipeline */
            if(!gst_bin_add (GST_BIN (pipeline->pipeline), instance_bin->sink_bin.sub_bins[i].bin)) {
                return FALSE;
            }
            /** link the broker sink bin to the common_elements tee
       * (The tee after nvinfer -> tracker (optional) -> sgies (optional) block) */
            if (!link_element_to_tee_src_pad (pipeline->common_elements.tee, instance_bin->sink_bin.sub_bins[i].bin)) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

gboolean Deepstream_source_code::is_sink_available_for_source_id(NvDsConfig *config, guint source_id)
{
    for (guint j = 0; j < config->num_sink_sub_bins; j++) {
        if (config->sink_bin_sub_bin_config[j].enable &&
                config->sink_bin_sub_bin_config[j].source_id == source_id) {
            return TRUE;
        }
    }
    return FALSE;
}

gboolean Deepstream_source_code::watch_source_status(gpointer data)
{
    NvDsSrcBin *src_bin = (NvDsSrcBin *) data;

    g_print ("watch_source_status %s\n", GST_ELEMENT_NAME(src_bin));
    if (src_bin && src_bin->reconfiguring) {
        // source is still not up, reconfigure it again.
        g_timeout_add (20, reset_source_pipeline, src_bin);
        return TRUE;
    } else {
        // source is reconfigured, remove call back.
        return FALSE;
    }
}

gboolean Deepstream_source_code::bus_callback(GstBus *bus, GstMessage *message, gpointer data)
{
    AppCtx *appCtx = (AppCtx *) data;
    GST_CAT_DEBUG (NVDS_APP,
                   "Received message on bus: source %s, msg_type %s",
                   GST_MESSAGE_SRC_NAME (message), GST_MESSAGE_TYPE_NAME (message));
    switch (GST_MESSAGE_TYPE (message)) {
    case GST_MESSAGE_INFO:{
        GError *error = NULL;
        gchar *debuginfo = NULL;
        gst_message_parse_info (message, &error, &debuginfo);
        g_printerr ("INFO from %s: %s\n",
                    GST_OBJECT_NAME (message->src), error->message);
        if (debuginfo) {
            g_printerr ("Debug info: %s\n", debuginfo);
        }
        g_error_free (error);
        g_free (debuginfo);
        break;
    }
    case GST_MESSAGE_WARNING:{
        GError *error = NULL;
        gchar *debuginfo = NULL;
        gst_message_parse_warning (message, &error, &debuginfo);
        g_printerr ("WARNING from %s: %s\n",
                    GST_OBJECT_NAME (message->src), error->message);
        if (debuginfo) {
            g_printerr ("Debug info: %s\n", debuginfo);
        }
        g_error_free (error);
        g_free (debuginfo);
        break;
    }
    case GST_MESSAGE_ERROR:{
        GError *error = NULL;
        gchar *debuginfo = NULL;
        guint i = 0;
        gst_message_parse_error (message, &error, &debuginfo);
        g_printerr ("ERROR from %s: %s\n",
                    GST_OBJECT_NAME (message->src), error->message);
        if (debuginfo) {
            g_printerr ("Debug info: %s\n", debuginfo);
        }

        NvDsSrcParentBin *bin = &appCtx->pipeline.multi_src_bin;
        GstElement *msg_src_elem = (GstElement *) GST_MESSAGE_SRC (message);
        gboolean bin_found = FALSE;
        /* Find the source bin which generated the error. */
        while (msg_src_elem && !bin_found) {
            for (i = 0; i < bin->num_bins && !bin_found; i++) {
                if (bin->sub_bins[i].src_elem == msg_src_elem ||
                        bin->sub_bins[i].bin == msg_src_elem) {
                    bin_found = TRUE;
                    break;
                }
            }
            msg_src_elem = GST_ELEMENT_PARENT (msg_src_elem);
        }

        if ((i != bin->num_bins) &&
                (appCtx->config.multi_source_config[0].type == NV_DS_SOURCE_RTSP)) {
            // Error from one of RTSP source.
            NvDsSrcBin *subBin = &bin->sub_bins[i];

            if (!subBin->reconfiguring ||
                    g_strrstr(debuginfo, "500 (Internal Server Error)")) {
                subBin->reconfiguring = TRUE;
                g_timeout_add (0, reset_source_pipeline, subBin);
            }
            g_error_free (error);
            g_free (debuginfo);
            return TRUE;
        }

        if (appCtx->config.multi_source_config[0].type == NV_DS_SOURCE_CAMERA_V4L2) {
            if (g_strrstr(debuginfo, "reason not-negotiated (-4)")) {
                NVGSTDS_INFO_MSG_V ("incorrect camera parameters provided, please provide supported resolution and frame rate\n");
            }

            if (g_strrstr(debuginfo, "Buffer pool activation failed")) {
                NVGSTDS_INFO_MSG_V ("usb bandwidth might be saturated\n");
            }
        }

        g_error_free (error);
        g_free (debuginfo);
        appCtx->return_value = -1;
        appCtx->quit = TRUE;
        break;
    }
    case GST_MESSAGE_STATE_CHANGED:{
        GstState oldstate, newstate;
        gst_message_parse_state_changed (message, &oldstate, &newstate, NULL);
        if (GST_ELEMENT (GST_MESSAGE_SRC (message)) == appCtx->pipeline.pipeline) {
            switch (newstate) {
            case GST_STATE_PLAYING:
                NVGSTDS_INFO_MSG_V ("Pipeline running\n");
                GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (appCtx->
                                                            pipeline.pipeline), GST_DEBUG_GRAPH_SHOW_ALL,
                                                   "ds-app-playing");
                break;
            case GST_STATE_PAUSED:
                if (oldstate == GST_STATE_PLAYING) {
                    NVGSTDS_INFO_MSG_V ("Pipeline paused\n");
                }
                break;
            case GST_STATE_READY:
                GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (appCtx->pipeline.
                                                            pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "ds-app-ready");
                if (oldstate == GST_STATE_NULL) {
                    NVGSTDS_INFO_MSG_V ("Pipeline ready\n");
                } else {
                    NVGSTDS_INFO_MSG_V ("Pipeline stopped\n");
                }
                break;
            case GST_STATE_NULL:
                g_mutex_lock (&appCtx->app_lock);
                g_cond_broadcast (&appCtx->app_cond);
                g_mutex_unlock (&appCtx->app_lock);
                break;
            default:
                break;
            }
        }
        break;
    }
    case GST_MESSAGE_EOS:{
        /*
          * In normal scenario, this would use g_main_loop_quit() to exit the
          * loop and release the resources. Since this application might be
          * running multiple pipelines through configuration files, it should wait
          * till all pipelines are done.
          */
        NVGSTDS_INFO_MSG_V ("Received EOS. Exiting ...\n");
        appCtx->quit = TRUE;
        return FALSE;
        break;
    }
    default:
        break;
    }
    return TRUE;
}

GstBusSyncReply Deepstream_source_code::bus_sync_handler(GstBus *bus, GstMessage *msg, gpointer data)
{
    AppCtx *appCtx = (AppCtx *) data;

    switch (GST_MESSAGE_TYPE (msg)) {
    case GST_MESSAGE_ELEMENT:
        if (GST_MESSAGE_SRC (msg) == GST_OBJECT (appCtx->pipeline.multi_src_bin.bin)) {
            const GstStructure *structure;
            structure = gst_message_get_structure (msg);

            if (gst_structure_has_name (structure, "GstBinForwarded")) {
                GstMessage *child_msg;

                if (gst_structure_has_field (structure, "message")) {
                    const GValue *val = gst_structure_get_value (structure, "message");
                    if (G_VALUE_TYPE (val) == GST_TYPE_MESSAGE) {
                        child_msg = (GstMessage *) g_value_get_boxed (val);
                        if (GST_MESSAGE_TYPE(child_msg) == GST_MESSAGE_ASYNC_DONE) {
                            guint i = 0;
                            NvDsSrcParentBin *bin = &appCtx->pipeline.multi_src_bin;
                            GST_DEBUG ("num bins: %d, message src: %s\n", bin->num_bins,
                                       GST_MESSAGE_SRC_NAME(child_msg));
                            for (i = 0; i < bin->num_bins; i++) {
                                if (bin->sub_bins[i].bin == (GstElement *) GST_MESSAGE_SRC (child_msg))
                                    break;
                            }

                            if (i != bin->num_bins) {
                                NvDsSrcBin *subBin = &bin->sub_bins[i];
                                if (subBin->reconfiguring &&
                                        appCtx->config.multi_source_config[0].type == NV_DS_SOURCE_RTSP)
                                    g_timeout_add (20, set_source_to_playing, subBin);
                            }
                        }
                    }
                }
            }
        }
        return GST_BUS_PASS;

    default:
        return GST_BUS_PASS;
    }
}

void Deepstream_source_code::write_kitti_output(AppCtx *appCtx, NvDsBatchMeta *batch_meta)
{
    gchar bbox_file[1024] = { 0 };
    FILE *bbox_params_dump_file = NULL;

    if (!appCtx->config.bbox_dir_path)
        return;

    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)l_frame->data;
        guint stream_id = frame_meta->pad_index;
        g_snprintf (bbox_file, sizeof (bbox_file) - 1,
                    "%s/%02u_%03u_%06lu.txt", appCtx->config.bbox_dir_path,
                    appCtx->index, stream_id, (gulong) frame_meta->frame_num);
        bbox_params_dump_file = fopen (bbox_file, "w");
        if (!bbox_params_dump_file)
            continue;

        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {
            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
            int left = obj->rect_params.left;
            int top = obj->rect_params.top;
            int right = left + obj->rect_params.width;
            int bottom = top + obj->rect_params.height;
            fprintf (bbox_params_dump_file,
                     "%s 0.0 0 0.0 %d.00 %d.00 %d.00 %d.00 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n",
                     obj->obj_label, left, top, right, bottom);
        }
        fclose (bbox_params_dump_file);
    }
}

void Deepstream_source_code::write_kitti_track_output(AppCtx *appCtx, NvDsBatchMeta *batch_meta)
{
    gchar bbox_file[1024] = { 0 };
    FILE *bbox_params_dump_file = NULL;

    if (!appCtx->config.kitti_track_dir_path)
        return;

    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) l_frame->data;
        guint stream_id = frame_meta->pad_index;
        g_snprintf (bbox_file, sizeof (bbox_file) - 1,
                    "%s/%02u_%03u_%06lu.txt", appCtx->config.kitti_track_dir_path,
                    appCtx->index, stream_id, (gulong) frame_meta->frame_num);
        bbox_params_dump_file = fopen (bbox_file, "w");
        if (!bbox_params_dump_file)
            continue;

        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {
            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
            int left = obj->rect_params.left;
            int top = obj->rect_params.top;
            int right = left + obj->rect_params.width;
            int bottom = top + obj->rect_params.height;
            guint64 id = obj->object_id;
            fprintf (bbox_params_dump_file,
                     "%s %lu 0.0 0 0.0 %d.00 %d.00 %d.00 %d.00 0.0 0.0 0.0 0.0 0.0 0.0 0.0\n",
                     obj->obj_label, id, left, top, right, bottom);
        }
        fclose (bbox_params_dump_file);
    }
}

gint Deepstream_source_code::component_id_compare_func(gconstpointer a, gconstpointer b)
{
    NvDsClassifierMeta *cmetaa = (NvDsClassifierMeta *) a;
    NvDsClassifierMeta *cmetab = (NvDsClassifierMeta *) b;

    if (cmetaa->unique_component_id < cmetab->unique_component_id)
        return -1;
    if (cmetaa->unique_component_id > cmetab->unique_component_id)
        return 1;
    return 0;
}
/**
 * Function to process the attached metadata. This is just for demonstration
 * and can be removed if not required.
 * Here it demonstrates to use bounding boxes of different color and size for
 * different type / class of objects.
 * It also demonstrates how to join the different labels(PGIE + SGIEs)
 * of an object to form a single string.
 */

void Deepstream_source_code::process_meta_test(AppCtx *appCtx, NvDsBatchMeta *batch_meta)
{

    //    qDebug() << "process_meta";
    //    // For single source always display text either with demuxer or with tiler
    //    if (!appCtx->config.tiled_display_config.enable ||
    //            appCtx->config.num_source_sub_bins == 1) {
    //        appCtx->show_bbox_text = 1;

    //    }

    //    gchar *str_color = NULL;

    //    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
    //         l_frame = l_frame->next) {
    //        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) l_frame->data;
    ////        g_print("source id = %d\n", frame_meta->source_id);
    //        int t1=0, r1=0, l2=0, t2=0, first_obj = 0;
    //        cv::Mat *prev;

    //        std::vector<std::pair<std::pair<int, int>, cv::Mat *>> object_l_t;
    ////        std::vector<std::pair<int, int>> object_l_t;

    //        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
    //             l_obj = l_obj->next) {
    //            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
    //            gint class_index = obj->class_id;
    //            NvDsGieConfig *gie_config = NULL;
    //            gchar *str_ins_pos = NULL;
    //            if(obj->class_id == 0){
    //                if(first_obj == 0){

    //                    std::pair<int, int> val;
    //                    val.first = obj->rect_params.left;
    //                    val.second = obj->rect_params.top;

    //                    cv::Mat *metadatap;

    //                    for (NvDsMetaList * p_user_meta = obj->obj_user_meta_list; p_user_meta != NULL;
    //                         p_user_meta = p_user_meta->next){

    //                        NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
    //                        metadatap = (cv::Mat*) user_metap->user_meta_data;
    //                    }

    //                    std::pair<std::pair<int, int>, cv::Mat*> val2;
    //                    val2.first = val;
    //                    val2.second = metadatap;

    //                    object_l_t.push_back(val2);

    //                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
    //                    r1 = obj->rect_params.top;
    //                    prev = metadatap;
    //                }else{

    //                    cv::Mat *metadatap;

    //                    for (NvDsMetaList * p_user_meta = obj->obj_user_meta_list; p_user_meta != NULL;
    //                         p_user_meta = p_user_meta->next){

    //                        NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
    //                        metadatap = (cv::Mat*) user_metap->user_meta_data;
    //                    }

    //                    l2 = obj->rect_params.left;
    //                    t2 = obj->rect_params.top;

    //                    cv::Point p1(t1, r1);
    //                    cv::Point p2(l2, t2);
    //                    double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
    //                    qDebug() << "Ressssssssssssss -> " << res;
    //                    if(res<3 && res>0){
    //                        obj->rect_params.has_bg_color = 1;
    //                        obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};



    //                        MainWindow::fromDsToMain(prev->clone(), metadatap->clone());
    //                    }


    //                    for(int i = 0; i < object_l_t.size(); i++){

    //                        cv::Point p11(t1, r1);
    //                        cv::Point p22(object_l_t.at(i).first.first, object_l_t.at(i).first.second);
    //                        double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
    ////                        qDebug() << "Ressssssssssssss -> " << res;
    //                        if(res<3 && res>0){
    //                            obj->rect_params.has_bg_color = 1;
    //                            obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};

    //                            MainWindow::fromDsToMain(prev->clone(), object_l_t.at(i).second->clone());

    //                        }
    //                    }

    //                    std::pair<int, int> val;
    //                    val.first = l2;
    //                    val.second = t2;

    ////                    cv::Mat *metadatap;

    ////                    for (NvDsMetaList * p_user_meta = obj->obj_user_meta_list; p_user_meta != NULL;
    ////                         p_user_meta = p_user_meta->next){

    ////                        NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
    ////                        metadatap = (cv::Mat*) user_metap->user_meta_data;
    ////                    }

    //                    std::pair<std::pair<int, int>, cv::Mat*> val2;
    //                    val2.first = val;
    //                    val2.second = metadatap;

    //                    object_l_t.push_back(val2);

    //                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
    //                    r1 = obj->rect_params.top;
    //                    prev = metadatap;
    //                }
    //                first_obj++;
    //            }
    //        }
    //        object_l_t.clear();
    //    }



    qDebug() << "process_meta";
    // For single source always display text either with demuxer or with tiler
    if (!appCtx->config.tiled_display_config.enable ||
            appCtx->config.num_source_sub_bins == 1) {
        appCtx->show_bbox_text = 1;

    }

    gchar *str_color = NULL;

    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) l_frame->data;
        //        g_print("source id = %d\n", frame_meta->source_id);
        int t1=0, r1=0, l2=0, t2=0, first_obj = 0;
        std::vector<std::pair<int, int>> object_l_t;

        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {
            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
            gint class_index = obj->class_id;
            NvDsGieConfig *gie_config = NULL;
            gchar *str_ins_pos = NULL;
            if(obj->class_id == 0){
                if(first_obj == 0){

                    std::pair<int, int> val;
                    val.first = obj->rect_params.left;
                    val.second = obj->rect_params.top;
                    object_l_t.push_back(val);

                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
                    r1 = obj->rect_params.top;
                }else{

                    //                    NvDsDisplayMeta *display_meta;
                    //                    display_meta = nvds_acquire_display_meta_from_pool (batch_meta);

                    //                    NvOSD_LineParams *line_params  = &display_meta->line_params[0];

                    //                    display_meta->num_lines = 1;

                    l2 = obj->rect_params.left;
                    t2 = obj->rect_params.top;


                    //                    line_params[0].x1 = t1;
                    //                    line_params[0].y1 = r1;
                    //                    line_params[0].x2 = l2;
                    //                    line_params[0].y2 = t2;
                    ////                    qDebug() << "Source Id = " << frame_meta->source_id
                    ////                             <<" Source width = " << frame_meta->source_frame_width
                    ////                             << " Source height = "
                    ////                             << frame_meta->source_frame_height
                    ////                             << " Person previous l and t "<< t1 << " " << r1
                    ////                             << " Person present l and t " << l2 << " " << t2;

                    //                    line_params[0].line_width = 5;

                    //                    cv::Point p1(t1, r1);
                    //                    cv::Point p2(l2, t2);
                    //                    double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
                    ////                    g_print("Distance = %.2f\n", res);
                    //                    if(res<6 && res>0){
                    //                        line_params[0].line_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 0.5};
                    //                    }else if(res>6){
                    //                        line_params[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 0.5};
                    //                    }



                    cv::Point p1(t1, r1);
                    cv::Point p2(l2, t2);
                    double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
                    //                    qDebug() << "Ressssssssssssss -> " << res;
                    if(res<3 && res>0){
                        obj->rect_params.has_bg_color = 1;
                        obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
                    }


                    for(int i = 0; i < object_l_t.size(); i++){
                        //                        NvDsDisplayMeta *display_meta1;
                        //                        display_meta1 = nvds_acquire_display_meta_from_pool (batch_meta);
                        //                        NvOSD_LineParams *line_params1  = &display_meta1->line_params[0];

                        //                        display_meta1->num_lines = 1;

                        //                        line_params1[0].x1 = t1;
                        //                        line_params1[0].y1 = r1;
                        //                        line_params1[0].x2 = object_l_t.at(i).first;
                        //                        line_params1[0].y2 = object_l_t.at(i).second;


                        //                        line_params1[0].line_width = 5;

                        //                        cv::Point p11(t1, r1);
                        //                        cv::Point p22(object_l_t.at(i).first, object_l_t.at(i).second);
                        //                        res = (cv::norm(p11-p22))/64; // Calibration factor = 64
                        ////                        g_print("Distance = %.2f\n", res);
                        //                        if(res<6 && res>0){
                        //                            line_params1[0].line_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 0.5};
                        //                        }else if(res>6){
                        //                            line_params1[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 0.5};
                        //                        }

                        cv::Point p11(t1, r1);
                        cv::Point p22(object_l_t.at(i).first, object_l_t.at(i).second);
                        double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
                        //                        qDebug() << "Ressssssssssssss -> " << res;
                        if(res<3 && res>0){
                            obj->rect_params.has_bg_color = 1;
                            obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
                        }
                    }

                    std::pair<int, int> val;
                    val.first = l2;
                    val.second = t2;
                    object_l_t.push_back(val);

                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
                    r1 = obj->rect_params.top;
                }
                first_obj++;
            }
        }
        object_l_t.clear();
    }


    //    qDebug() << "process_meta";
    //    //    // For single source always display text either with demuxer or with tiler
    //    //    if (!appCtx->config.tiled_display_config.enable ||
    //    //            appCtx->config.num_source_sub_bins == 1) {
    //    appCtx->show_bbox_text = 1;

    //    //    }

    //    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
    //         l_frame = l_frame->next) {
    //        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) l_frame->data;

    //        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
    //             l_obj = l_obj->next) {
    //            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
    //            if(obj->class_id == 0){
    //                for(NvDsMetaList * p_obj = frame_meta->obj_meta_list; p_obj != NULL;
    //                    p_obj = p_obj->next){
    //                    NvDsObjectMeta *pobj = (NvDsObjectMeta *) p_obj->data;
    //                    if(pobj->class_id == 0){
    ////                        if(obj->rect_params.left != pobj->rect_params.left && obj->rect_params.top != pobj->rect_params.top){
    //                            cv::Point p1(obj->rect_params.left, obj->rect_params.top);
    //                            cv::Point p2(pobj->rect_params.left, pobj->rect_params.top);
    //                            double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
    //                            qDebug() << "Ressssssssssssss -> " << res;
    //                            if(res<3 && res>0){
    //                                pobj->rect_params.has_bg_color = 1;
    //                                pobj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};

    //                                cv::Mat *metadatap;cv::Mat *metadata;

    //                                for (NvDsMetaList * p_user_meta = obj->obj_user_meta_list; p_user_meta != NULL;
    //                                     p_user_meta = p_user_meta->next){

    //                                    NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
    //                                    metadatap = (cv::Mat*) user_metap->user_meta_data;
    //                                }
    //                                for (NvDsMetaList * f_user_meta = pobj->obj_user_meta_list; f_user_meta != NULL;
    //                                     f_user_meta = f_user_meta->next){

    //                                    NvDsUserMeta * user_meta = (NvDsUserMeta *) (f_user_meta->data);
    //                                    metadata = (cv::Mat*) user_meta->user_meta_data;
    //                                }

    ////                                watchcam::rectangle rect(pobj->rect_params.left,pobj->rect_params.top,pobj->rect_params.width,pobj->rect_params.height);
    ////                                rect.source_id = 0;
    ////                                rect.mask_or_unmask = "mask_or_unmask";
    ////                                rect.str_color = "person_color";
    ////                                rect.fps = fps[0];
    ////                                MainWindow::fromDsToMain(metadatap->clone(), metadata->clone(), rect);

    //                                //                                        line_params[0].line_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 0.5};
    //                            }else if(res>6){
    //                                //                                        aperson_meta->rect_params.has_bg_color = 1;
    ////                                pobj->rect_params.bg_color = (NvOSD_ColorParams) {0.0, 1.0, 0.0, 0.5};
    //                                //                                        line_params[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 0.5};
    //                            }
    ////                        }
    //                    }
    //                }
    //            }
    //        }

    //    }
}

void Deepstream_source_code::process_meta (AppCtx * appCtx, NvDsBatchMeta * batch_meta)
{
    gchar clear[10] = "clear";
    gchar masked[10] = "masked";
    appCtx->show_bbox_text = 1;

    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {

        NvDsFrameMeta *frame_meta = (NvDsFrameMeta*)l_frame->data;

        int source_id = (int) frame_meta->source_id;

        //        qDebug() << "Strat of frame .................................> " << source_id;
        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {

            NvDsObjectMeta * obj_meta = (NvDsObjectMeta *) (l_obj->data);

            if(obj_meta->class_id == 2){

                for (NvDsMetaList * p_obj = frame_meta->obj_meta_list; p_obj != NULL;
                     p_obj = p_obj->next){

                    NvDsObjectMeta *person_meta = (NvDsObjectMeta*) (p_obj->data);

                    NvDsBatchMeta *batch_meta_f = frame_meta->base_meta.batch_meta;
                    NvDsDisplayMeta *display_meta_disp = nvds_acquire_display_meta_from_pool(batch_meta_f);

                    if(person_meta->class_id == 0){

                        int pl = person_meta->rect_params.left;
                        int pt = person_meta->rect_params.top;
                        int pw = person_meta->rect_params.width;
                        int ph = person_meta->rect_params.height;

                        int fl = obj_meta->rect_params.left;
                        int ft = obj_meta->rect_params.top;
                        int fw = obj_meta->rect_params.width;
                        int fh = obj_meta->rect_params.height;



                        if((pl<=fl && pt<=ft) &&
                                ((pl+pw)>=(fl+fw) && pt<=ft) && (pl<=fl &&
                                                                 (pt+ph)>=(ft+fh)) && ((pl+pw)>=(fl+fw) && (pt+ph)>=(ft+fh))){

                            watchcam::rectangle rect(person_meta->rect_params.left,person_meta->rect_params.top,person_meta->rect_params.width,person_meta->rect_params.height);
                            rect.source_id = source_id;

                            for (NvDsMetaList * ap_obj = frame_meta->obj_meta_list; ap_obj != NULL;
                                 ap_obj = ap_obj->next){

                                NvDsObjectMeta *aperson_meta = (NvDsObjectMeta*) (ap_obj->data);

                                cv::Point p1(pl, pt);
                                cv::Point p2(aperson_meta->rect_params.left, aperson_meta->rect_params.top);
                                double res = (cv::norm(p1-p2))/64;

                                if(aperson_meta->class_id == 0 && (res<3 && res>2.5) &&
                                        aperson_meta->unique_component_id != person_meta->unique_component_id){

                                    //                                    cv::Mat *metadata;

                                    //                                    for (NvDsMetaList * p_user_meta = aperson_meta->obj_user_meta_list; p_user_meta != NULL;
                                    //                                         p_user_meta = p_user_meta->next){

                                    //                                        NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
                                    //                                        metadata = (cv::Mat*) user_metap->user_meta_data;

                                    //                                    }
                                    aperson_meta->rect_params.has_bg_color = 1;
                                    aperson_meta->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
                                    //                                    std::pair<cv::Mat*, float> per;
                                    //                                    per.first = metadata;
                                    //                                    per.second = res;
                                    //                                    rect.person.push_back(per);

                                }
                            }
                            cv::Mat *metadatap;cv::Mat *metadata;

                            for (NvDsMetaList * p_user_meta = person_meta->obj_user_meta_list; p_user_meta != NULL;
                                 p_user_meta = p_user_meta->next){

                                NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
                                metadatap = (cv::Mat*) user_metap->user_meta_data;
                            }
                            for (NvDsMetaList * f_user_meta = obj_meta->obj_user_meta_list; f_user_meta != NULL;
                                 f_user_meta = f_user_meta->next){

                                NvDsUserMeta * user_meta = (NvDsUserMeta *) (f_user_meta->data);
                                metadata = (cv::Mat*) user_meta->user_meta_data;

                                std::string person_color, mask_or_unmask;
                                person_color = "Unknown";
                                mask_or_unmask = "Unknown";

                                NvDsGieConfig *gie_config = NULL;

                                // mask or unmask
                                gie_config = &appCtx->config.secondary_gie_sub_bin_config[1];

                                if (6 == (gint) gie_config->unique_id){


                                    for (NvDsMetaList * l_class = obj_meta->classifier_meta_list; l_class != NULL;
                                         l_class = l_class->next) {
                                        //                                qDebug() << "9999999999999999999999999999999999999999";
                                        NvDsClassifierMeta *cmeta = (NvDsClassifierMeta *) l_class->data;
                                        for (NvDsMetaList * l_label = cmeta->label_info_list; l_label != NULL;
                                             l_label = l_label->next) {
                                            NvDsLabelInfo *label = (NvDsLabelInfo *) l_label->data;

                                            if (label->pResult_label) {
                                            }
                                            else if (label->result_label[0] != '\0') {
                                                gchar* str_color = NULL;
                                                str_color = g_strdup_printf("%s",label->result_label);
                                                if(strcmp(str_color,masked) == 0)
                                                {
                                                    //sprintf (str_ins_pos, " %s", clear);
                                                    obj_meta->rect_params.has_bg_color = 1;obj_meta->rect_params.bg_color = (NvOSD_ColorParams) {0,1, 0, 0.5};
                                                    g_print( ">>>>>>>>>>>>>>>>>>>>>> MAASSKKEEDD = %s ",str_color);
                                                }
                                                if(QString::compare(str_color, "Obj_label") != 0){
                                                    qDebug() << "......................" << str_color;
                                                    mask_or_unmask = str_color;
                                                }
                                            }
                                        }
                                        break;
                                        gie_config = NULL;
                                    }
                                }
                                // color
                                gie_config = &appCtx->config.secondary_gie_sub_bin_config[0];

                                if (5 == (gint) gie_config->unique_id){


                                    for (NvDsMetaList * l_class = person_meta->classifier_meta_list; l_class != NULL;
                                         l_class = l_class->next) {
                                        //                                qDebug() << "9999999999999999999999999999999999999999";
                                        NvDsClassifierMeta *cmeta = (NvDsClassifierMeta *) l_class->data;
                                        for (NvDsMetaList * l_label = cmeta->label_info_list; l_label != NULL;
                                             l_label = l_label->next) {
                                            NvDsLabelInfo *label = (NvDsLabelInfo *) l_label->data;

                                            if (label->pResult_label) {
                                            }
                                            else if (label->result_label[0] != '\0') {
                                                gchar* str_color = NULL;
                                                str_color = g_strdup_printf("%s",label->result_label);
                                                if(QString::compare(str_color, "Obj_label") != 0){
                                                    qDebug() << "......................" << str_color;
                                                    person_color = str_color;
                                                }
                                            }
                                        }
                                        break;
                                        gie_config = NULL;
                                    }
                                }


                                //                        qDebug() << "dhan start";

                                rect.mask_or_unmask = mask_or_unmask;
                                rect.str_color = person_color;
                                rect.fps = fps[0];


                                MainWindow::fromDsToMain(metadatap, metadata, rect);

                            }
                        }

                    }

                }
                break;
            }

        }
    }

}
//void Deepstream_source_code::process_meta(AppCtx *appCtx, NvDsBatchMeta *batch_meta)
//{
//    qDebug() << "process_meta";
//    // For single source always display text either with demuxer or with tiler
//    if (!appCtx->config.tiled_display_config.enable ||
//            appCtx->config.num_source_sub_bins == 1) {
//        appCtx->show_bbox_text = 1;

//    }

//    gchar *str_color = NULL;

//    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
//         l_frame = l_frame->next) {
//        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *) l_frame->data;
////        g_print("source id = %d\n", frame_meta->source_id);
//        int t1=0, r1=0, l2=0, t2=0, first_obj = 0;
//        std::vector<std::pair<int, int>> object_l_t;

//        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
//             l_obj = l_obj->next) {
//            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
//            gint class_index = obj->class_id;
//            NvDsGieConfig *gie_config = NULL;
//            gchar *str_ins_pos = NULL;
//            if(obj->class_id == 0){
//                if(first_obj == 0){

//                    std::pair<int, int> val;
//                    val.first = obj->rect_params.left;
//                    val.second = obj->rect_params.top;
//                    object_l_t.push_back(val);

//                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
//                    r1 = obj->rect_params.top;
//                }else{

////                    NvDsDisplayMeta *display_meta;
////                    display_meta = nvds_acquire_display_meta_from_pool (batch_meta);

////                    NvOSD_LineParams *line_params  = &display_meta->line_params[0];

////                    display_meta->num_lines = 1;

////                    l2 = obj->rect_params.left;
////                    t2 = obj->rect_params.top;


////                    line_params[0].x1 = t1;
////                    line_params[0].y1 = r1;
////                    line_params[0].x2 = l2;
////                    line_params[0].y2 = t2;
//////                    qDebug() << "Source Id = " << frame_meta->source_id
//////                             <<" Source width = " << frame_meta->source_frame_width
//////                             << " Source height = "
//////                             << frame_meta->source_frame_height
//////                             << " Person previous l and t "<< t1 << " " << r1
//////                             << " Person present l and t " << l2 << " " << t2;

////                    line_params[0].line_width = 5;

////                    cv::Point p1(t1, r1);
////                    cv::Point p2(l2, t2);
////                    double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
//////                    g_print("Distance = %.2f\n", res);
////                    if(res<6 && res>0){
////                        line_params[0].line_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 0.5};
////                    }else if(res>6){
////                        line_params[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 0.5};
////                    }



//                    cv::Point p1(t1, r1);
//                    cv::Point p2(l2, t2);
//                    double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
//                    qDebug() << "Ressssssssssssss -> " << res;
//                    if(res<3 && res>0){
//                        obj->rect_params.has_bg_color = 1;
//                        obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
//                    }


//                    for(int i = 0; i < object_l_t.size(); i++){
////                        NvDsDisplayMeta *display_meta1;
////                        display_meta1 = nvds_acquire_display_meta_from_pool (batch_meta);
////                        NvOSD_LineParams *line_params1  = &display_meta1->line_params[0];

////                        display_meta1->num_lines = 1;

////                        line_params1[0].x1 = t1;
////                        line_params1[0].y1 = r1;
////                        line_params1[0].x2 = object_l_t.at(i).first;
////                        line_params1[0].y2 = object_l_t.at(i).second;


////                        line_params1[0].line_width = 5;

////                        cv::Point p11(t1, r1);
////                        cv::Point p22(object_l_t.at(i).first, object_l_t.at(i).second);
////                        res = (cv::norm(p11-p22))/64; // Calibration factor = 64
//////                        g_print("Distance = %.2f\n", res);
////                        if(res<6 && res>0){
////                            line_params1[0].line_color = (NvOSD_ColorParams){1.0, 0.0, 0.0, 0.5};
////                        }else if(res>6){
////                            line_params1[0].line_color = (NvOSD_ColorParams){0.0, 1.0, 0.0, 0.5};
////                        }

//                        cv::Point p11(t1, r1);
//                        cv::Point p22(object_l_t.at(i).first, object_l_t.at(i).second);
//                        double res = (cv::norm(p1-p2))/64; // Calibration factor = 64
////                        qDebug() << "Ressssssssssssss -> " << res;
//                        if(res<3 && res>0){
//                            obj->rect_params.has_bg_color = 1;
//                            obj->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
//                        }
//                    }

//                    std::pair<int, int> val;
//                    val.first = l2;
//                    val.second = t2;
//                    object_l_t.push_back(val);

//                    t1 = obj->rect_params.left/*+obj->rect_params.width*/;
//                    r1 = obj->rect_params.top;
//                }
//                first_obj++;
//            }
//        }
//        object_l_t.clear();
//    }
//}

void Deepstream_source_code::process_buffer(GstBuffer *buf, AppCtx *appCtx, guint index)
{
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
    if (!batch_meta) {
        NVGSTDS_WARN_MSG_V ("Batch meta not found for buffer %p", buf);
        return;
    }
    //    Deepstream_source_code::process_meta (appCtx, batch_meta);
    //    Deepstream_source_code::process_meta_test (appCtx, batch_meta);
    NvDsInstanceData *data = &appCtx->instance_data[index];
    guint i;

    data->frame_num++;

    /* Opportunity to modify the processed metadata or do analytics based on
   * type of object e.g. maintaining count of particular type of car.
   */
    if (appCtx->all_bbox_generated_cb) {
        appCtx->all_bbox_generated_cb (appCtx, buf, batch_meta, index);
    }
    //data->bbox_list_size = 0;

    /*
   * callback to attach application specific additional metadata.
   */
    if (appCtx->overlay_graphics_cb) {
        appCtx->overlay_graphics_cb (appCtx, buf, batch_meta, index);
    }
}

GstPadProbeReturn Deepstream_source_code::gie_primary_processing_done_buf_prob(GstPad *pad, GstPadProbeInfo *info, gpointer u_data)
{
    GstBuffer *buf = (GstBuffer *) info->data;
    AppCtx *appCtx = (AppCtx *) u_data;
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
    if (!batch_meta) {
        NVGSTDS_WARN_MSG_V ("Batch meta not found for buffer %p", buf);
        return GST_PAD_PROBE_OK;
    }

    Deepstream_source_code::write_kitti_output (appCtx, batch_meta);

    return GST_PAD_PROBE_OK;
}

GstPadProbeReturn Deepstream_source_code::gie_processing_done_buf_prob(GstPad *pad, GstPadProbeInfo *info, gpointer u_data)
{
    GstBuffer *buf = (GstBuffer *) info->data;
    NvDsInstanceBin *bin = (NvDsInstanceBin *) u_data;
    guint index = bin->index;
    AppCtx *appCtx = bin->appCtx;

    if (gst_buffer_is_writable (buf))
        Deepstream_source_code::process_buffer (buf, appCtx, index);
    return GST_PAD_PROBE_OK;
}

GstPadProbeReturn Deepstream_source_code::analytics_done_buf_prob(GstPad *pad, GstPadProbeInfo *info, gpointer u_data)
{
    NvDsInstanceBin *bin = (NvDsInstanceBin *) u_data;
    guint index = bin->index;
    AppCtx *appCtx = bin->appCtx;
    GstBuffer *buf = (GstBuffer *) info->data;
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
    if (!batch_meta) {
        NVGSTDS_WARN_MSG_V ("Batch meta not found for buffer %p", buf);
        return GST_PAD_PROBE_OK;
    }

    /*
   * Output KITTI labels with tracking ID if configured to do so.
   */
    Deepstream_source_code::write_kitti_track_output(appCtx, batch_meta);

    if (appCtx->bbox_generated_post_analytics_cb)
        appCtx->bbox_generated_post_analytics_cb (appCtx, buf, batch_meta, index);
    return GST_PAD_PROBE_OK;
}

GstPadProbeReturn Deepstream_source_code::latency_measurement_buf_prob(GstPad *pad, GstPadProbeInfo *info, gpointer u_data)
{
    AppCtx *appCtx = (AppCtx *) u_data;
    guint i = 0, num_sources_in_batch = 0;
    if(nvds_enable_latency_measurement)
    {
        GstBuffer *buf = (GstBuffer *) info->data;
        NvDsFrameLatencyInfo *latency_info = NULL;
        g_mutex_lock (&appCtx->latency_lock);
        latency_info = appCtx->latency_info;
        g_print("\n************BATCH-NUM = %d**************\n",batch_num);
        num_sources_in_batch = nvds_measure_buffer_latency(buf, latency_info);

        for(i = 0; i < num_sources_in_batch; i++)
        {
            g_print("Source id = %d Frame_num = %d Frame latency = %lf (ms) \n",
                    latency_info[i].source_id,
                    latency_info[i].frame_num,
                    latency_info[i].latency);
        }
        g_mutex_unlock (&appCtx->latency_lock);
        batch_num++;
    }

    return GST_PAD_PROBE_OK;
}

gboolean Deepstream_source_code::create_processing_instance(AppCtx *appCtx, guint index)
{
    gboolean ret = FALSE;
    NvDsConfig *config = &appCtx->config;
    NvDsInstanceBin *instance_bin = &appCtx->pipeline.instance_bins[index];
    GstElement *last_elem;
    gchar elem_name[32];

    instance_bin->index = index;
    instance_bin->appCtx = appCtx;

    g_snprintf (elem_name, 32, "processing_bin_%d", index);
    instance_bin->bin = gst_bin_new (elem_name);

    if (!create_sink_bin (config->num_sink_sub_bins,
                          config->sink_bin_sub_bin_config, &instance_bin->sink_bin, index)) {
        goto done;
    }

    gst_bin_add (GST_BIN (instance_bin->bin), instance_bin->sink_bin.bin);
    last_elem = instance_bin->sink_bin.bin;

    if (config->osd_config.enable) {
        if (!create_osd_bin (&config->osd_config, &instance_bin->osd_bin)) {
            goto done;
        }

        gst_bin_add (GST_BIN (instance_bin->bin), instance_bin->osd_bin.bin);

        NVGSTDS_LINK_ELEMENT (instance_bin->osd_bin.bin, last_elem);

        last_elem = instance_bin->osd_bin.bin;
    }

    NVGSTDS_BIN_ADD_GHOST_PAD (instance_bin->bin, last_elem, "sink");
    if (config->osd_config.enable) {
        NVGSTDS_ELEM_ADD_PROBE (instance_bin->all_bbox_buffer_probe_id,
                                instance_bin->osd_bin.nvosd, "sink",
                                Deepstream_source_code::gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
    } else {
        NVGSTDS_ELEM_ADD_PROBE (instance_bin->all_bbox_buffer_probe_id,
                                instance_bin->sink_bin.bin, "sink",
                                Deepstream_source_code::gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
    }

    ret = TRUE;
done:
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

gboolean Deepstream_source_code::create_common_elements(NvDsConfig *config, NvDsPipeline *pipeline, GstElement **sink_elem, GstElement **src_elem, bbox_generated_callback bbox_generated_post_analytics_cb)
{
    gboolean ret = FALSE;
    *sink_elem = *src_elem = NULL;

    if (config->primary_gie_config.enable) {
        if (config->num_secondary_gie_sub_bins > 0) {
            if (!create_secondary_gie_bin (config->num_secondary_gie_sub_bins,
                                           config->primary_gie_config.unique_id,
                                           config->secondary_gie_sub_bin_config,
                                           &pipeline->common_elements.secondary_gie_bin)) {
                goto done;
            }
            gst_bin_add (GST_BIN (pipeline->pipeline),
                         pipeline->common_elements.secondary_gie_bin.bin);
            if (!*src_elem) {
                *src_elem = pipeline->common_elements.secondary_gie_bin.bin;
            }
            if (*sink_elem) {
                NVGSTDS_LINK_ELEMENT (pipeline->common_elements.secondary_gie_bin.bin,
                                      *sink_elem);
            }
            *sink_elem = pipeline->common_elements.secondary_gie_bin.bin;
        }
    }

    if (config->tracker_config.enable) {
        if (!create_tracking_bin (&config->tracker_config,
                                  &pipeline->common_elements.tracker_bin)) {
            g_print ("creating tracker bin failed\n");
            goto done;
        }
        gst_bin_add (GST_BIN (pipeline->pipeline),
                     pipeline->common_elements.tracker_bin.bin);
        if (!*src_elem) {
            *src_elem = pipeline->common_elements.tracker_bin.bin;
        }
        if (*sink_elem) {
            NVGSTDS_LINK_ELEMENT (pipeline->common_elements.tracker_bin.bin,
                                  *sink_elem);
        }
        *sink_elem = pipeline->common_elements.tracker_bin.bin;
    }

    if (config->primary_gie_config.enable) {
        if (!create_primary_gie_bin (&config->primary_gie_config,
                                     &pipeline->common_elements.primary_gie_bin)) {
            goto done;
        }
        gst_bin_add (GST_BIN (pipeline->pipeline),
                     pipeline->common_elements.primary_gie_bin.bin);
        if (*sink_elem) {
            NVGSTDS_LINK_ELEMENT (pipeline->common_elements.primary_gie_bin.bin,
                                  *sink_elem);
        }
        *sink_elem = pipeline->common_elements.primary_gie_bin.bin;
        if (!*src_elem) {
            *src_elem = pipeline->common_elements.primary_gie_bin.bin;
        }
        NVGSTDS_ELEM_ADD_PROBE (pipeline->common_elements.
                                primary_bbox_buffer_probe_id,
                                pipeline->common_elements.primary_gie_bin.bin, "src",
                                Deepstream_source_code::gie_primary_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
                                pipeline->common_elements.appCtx);
    }

    if(*src_elem) {
        NVGSTDS_ELEM_ADD_PROBE (pipeline->common_elements.
                                primary_bbox_buffer_probe_id,
                                *src_elem, "src",
                                Deepstream_source_code::analytics_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
                                &pipeline->common_elements);
        pipeline->common_elements.tee = gst_element_factory_make (NVDS_ELEM_TEE, "common_analytics_tee");
        if (!pipeline->common_elements.tee) {
            NVGSTDS_ERR_MSG_V ("Failed to create element 'common_analytics_tee'");
            goto done;
        }

        gst_bin_add (GST_BIN (pipeline->pipeline),
                     pipeline->common_elements.tee);

        NVGSTDS_LINK_ELEMENT (*src_elem, pipeline->common_elements.tee);
        *src_elem = pipeline->common_elements.tee;
    }

    ret = TRUE;
done:
    return ret;
}

gboolean Deepstream_source_code::create_demux_pipeline (AppCtx * appCtx, guint index)
{
    gboolean ret = FALSE;
    NvDsConfig *config = &appCtx->config;
    NvDsInstanceBin *instance_bin = &appCtx->pipeline.demux_instance_bins[index];
    GstElement *last_elem;
    gchar elem_name[32];

    instance_bin->index = index;
    instance_bin->appCtx = appCtx;

    g_snprintf (elem_name, 32, "processing_demux_bin_%d", index);
    instance_bin->bin = gst_bin_new (elem_name);

    if (!create_demux_sink_bin (config->num_sink_sub_bins,
                                config->sink_bin_sub_bin_config, &instance_bin->demux_sink_bin,
                                config->sink_bin_sub_bin_config[index].source_id)) {
        goto done;
    }

    gst_bin_add (GST_BIN (instance_bin->bin), instance_bin->demux_sink_bin.bin);
    last_elem = instance_bin->demux_sink_bin.bin;

    if (config->osd_config.enable) {
        if (!create_osd_bin (&config->osd_config, &instance_bin->osd_bin)) {
            goto done;
        }

        gst_bin_add (GST_BIN (instance_bin->bin), instance_bin->osd_bin.bin);

        NVGSTDS_LINK_ELEMENT (instance_bin->osd_bin.bin, last_elem);

        last_elem = instance_bin->osd_bin.bin;
    }

    NVGSTDS_BIN_ADD_GHOST_PAD (instance_bin->bin, last_elem, "sink");
    if (config->osd_config.enable) {
        NVGSTDS_ELEM_ADD_PROBE (instance_bin->all_bbox_buffer_probe_id,
                                instance_bin->osd_bin.nvosd, "sink",
                                gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
    } else {
        NVGSTDS_ELEM_ADD_PROBE (instance_bin->all_bbox_buffer_probe_id,
                                instance_bin->demux_sink_bin.bin, "sink",
                                gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
    }

    ret = TRUE;
done:
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

GstPadProbeReturn Deepstream_source_code::demux_latency_measurement_buf_prob(GstPad * pad, GstPadProbeInfo * info, gpointer u_data)
{
    AppCtx *appCtx = (AppCtx *) u_data;
    guint i = 0, num_sources_in_batch = 0;
    if(nvds_enable_latency_measurement)
    {
        GstBuffer *buf = (GstBuffer *) info->data;
        NvDsFrameLatencyInfo *latency_info = NULL;
        g_mutex_lock (&appCtx->latency_lock);
        latency_info = appCtx->latency_info;
        g_print("\n************DEMUX BATCH-NUM = %d**************\n",demux_batch_num);
        num_sources_in_batch = nvds_measure_buffer_latency(buf, latency_info);

        for(i = 0; i < num_sources_in_batch; i++)
        {
            g_print("Source id = %d Frame_num = %d Frame latency = %lf (ms) \n",
                    latency_info[i].source_id,
                    latency_info[i].frame_num,
                    latency_info[i].latency);
        }
        g_mutex_unlock (&appCtx->latency_lock);
        demux_batch_num++;
    }

    return GST_PAD_PROBE_OK;
}


gboolean Deepstream_source_code::create_pipeline(AppCtx *appCtx, bbox_generated_callback bbox_generated_post_analytics_cb, bbox_generated_callback all_bbox_generated_cb, perf_callback perf_cb, overlay_graphics_callback overlay_graphics_cb)
{
    gboolean ret = FALSE;
    NvDsPipeline *pipeline = &appCtx->pipeline;
    NvDsConfig *config = &appCtx->config;
    GstBus *bus;
    GstElement *last_elem;
    GstElement *tmp_elem1;
    GstElement *tmp_elem2;
    guint i;
    GstPad *fps_pad;
    gulong latency_probe_id;
    gulong dsexample_probe_id = 15;

    _dsmeta_quark = g_quark_from_static_string (NVDS_META_STRING);

    appCtx->all_bbox_generated_cb = all_bbox_generated_cb;
    appCtx->bbox_generated_post_analytics_cb = bbox_generated_post_analytics_cb;
    appCtx->overlay_graphics_cb = overlay_graphics_cb;

    if (config->osd_config.num_out_buffers < 8) {
        config->osd_config.num_out_buffers = 8;
    }

    pipeline->pipeline = gst_pipeline_new ("pipeline");
    if (!pipeline->pipeline) {
        NVGSTDS_ERR_MSG_V ("Failed to create pipeline");
        goto done;
    }

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline->pipeline));
    pipeline->bus_id = gst_bus_add_watch (bus, Deepstream_source_code::bus_callback, appCtx);
    gst_object_unref (bus);

    if (config->file_loop) {
        /* Let each source bin know it needs to loop. */
        guint i;
        for (i = 0; i < config->num_source_sub_bins; i++)
            config->multi_source_config[i].loop = TRUE;
    }

    for (guint i = 0; i < config->num_sink_sub_bins; i++) {
        NvDsSinkSubBinConfig *sink_config = &config->sink_bin_sub_bin_config[i];
        switch (sink_config->type) {
        case NV_DS_SINK_FAKE:
        case NV_DS_SINK_RENDER_EGL:
        case NV_DS_SINK_RENDER_OVERLAY:
            /* Set the "qos" property of sink, if not explicitly specified in the
               config. */
            if (!sink_config->render_config.qos_value_specified) {
                /* QoS events should be generated by sink always in case of live sources
                 or with synchronous playback for non-live sources. */
                if (config->streammux_config.live_source || sink_config->render_config.sync) {
                    sink_config->render_config.qos = TRUE;
                } else {
                    sink_config->render_config.qos = FALSE;
                }
            }
        default:
            break;
        }
    }
    /*
       * Add muxer and < N > source components to the pipeline based
       * on the settings in configuration file.
       */
    if (!create_multi_source_bin (config->num_source_sub_bins,
                                  config->multi_source_config, &pipeline->multi_src_bin))
        goto done;
    gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->multi_src_bin.bin);


    if (config->streammux_config.is_parsed)
        set_streammux_properties (&config->streammux_config,
                                  pipeline->multi_src_bin.streammux);

    if(appCtx->latency_info == NULL)
    {
        appCtx->latency_info = (NvDsFrameLatencyInfo *)
                calloc(1, config->streammux_config.batch_size *
                       sizeof(NvDsFrameLatencyInfo));
    }

    /** a tee after the tiler which shall be connected to sink(s) */
    pipeline->tiler_tee = gst_element_factory_make (NVDS_ELEM_TEE, "tiler_tee");
    if (!pipeline->tiler_tee) {
        NVGSTDS_ERR_MSG_V ("Failed to create element 'tiler_tee'");
        goto done;
    }
    gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->tiler_tee);

    /** Tiler + Demux in Parallel Use-Case */
    if (config->tiled_display_config.enable == NV_DS_TILED_DISPLAY_ENABLE_WITH_PARALLEL_DEMUX)
    {
        pipeline->demuxer =
                gst_element_factory_make (NVDS_ELEM_STREAM_DEMUX, "demuxer");
        if (!pipeline->demuxer) {
            NVGSTDS_ERR_MSG_V ("Failed to create element 'demuxer'");
            goto done;
        }
        gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->demuxer);

        /** NOTE:
         * demux output is supported for only one source
         * If multiple [sink] groups are configured with
         * link_to_demux=1, only the first [sink]
         * shall be constructed for all occurences of
         * [sink] groups with link_to_demux=1
         */
        {
            gchar pad_name[16];
            GstPad *demux_src_pad;

            i = 0;
            if (!Deepstream_source_code::create_demux_pipeline (appCtx, i)) {
                goto done;
            }

            for (i=0; i < config->num_sink_sub_bins; i++)
            {
                if (config->sink_bin_sub_bin_config[i].link_to_demux == TRUE)
                {
                    g_snprintf (pad_name, 16, "src_%02d", config->sink_bin_sub_bin_config[i].source_id);
                    break;
                }
            }

            if (i >= config->num_sink_sub_bins)
            {
                g_print ("\n\nError : sink for demux (use link-to-demux-only property) is not provided in the config file\n\n");
                goto done;
            }

            i = 0;

            gst_bin_add (GST_BIN (pipeline->pipeline),
                         pipeline->demux_instance_bins[i].bin);

            demux_src_pad = gst_element_get_request_pad (pipeline->demuxer, pad_name);
            NVGSTDS_LINK_ELEMENT_FULL (pipeline->demuxer, pad_name,
                                       pipeline->demux_instance_bins[i].bin, "sink");
            gst_object_unref (demux_src_pad);

            NVGSTDS_ELEM_ADD_PROBE(latency_probe_id,
                                   appCtx->pipeline.demux_instance_bins[i].demux_sink_bin.bin,
                                   "sink",
                                   Deepstream_source_code::demux_latency_measurement_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
                                   appCtx);
            latency_probe_id = latency_probe_id;
        }

        last_elem = pipeline->demuxer;
        link_element_to_tee_src_pad (pipeline->tiler_tee, last_elem);
        last_elem = pipeline->tiler_tee;
    }

    if (config->tiled_display_config.enable) {

        /* Tiler will generate a single composited buffer for all sources. So need
         * to create only one processing instance. */
        if (!create_processing_instance (appCtx, 0)) {
            goto done;
        }
        // create and add tiling component to pipeline.
        if (config->tiled_display_config.columns *
                config->tiled_display_config.rows < config->num_source_sub_bins) {
            if (config->tiled_display_config.columns == 0) {
                config->tiled_display_config.columns =
                        (guint) (sqrt (config->num_source_sub_bins) + 0.5);
            }
            config->tiled_display_config.rows =
                    (guint) ceil (1.0 * config->num_source_sub_bins /
                                  config->tiled_display_config.columns);
            NVGSTDS_WARN_MSG_V
                    ("Num of Tiles less than number of sources, readjusting to "
                     "%u rows, %u columns", config->tiled_display_config.rows,
                     config->tiled_display_config.columns);
        }

        gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->instance_bins[0].bin);
        last_elem = pipeline->instance_bins[0].bin;

        if (!create_tiled_display_bin (&config->tiled_display_config,
                                       &pipeline->tiled_display_bin)) {
            goto done;
        }
        gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->tiled_display_bin.bin);
        NVGSTDS_LINK_ELEMENT (pipeline->tiled_display_bin.bin, last_elem);
        last_elem = pipeline->tiled_display_bin.bin;

        link_element_to_tee_src_pad (pipeline->tiler_tee, pipeline->tiled_display_bin.bin);
        last_elem = pipeline->tiler_tee;

        NVGSTDS_ELEM_ADD_PROBE (latency_probe_id,
                                pipeline->instance_bins->sink_bin.sub_bins[0].sink, "sink",
                latency_measurement_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
                appCtx);
        latency_probe_id = latency_probe_id;
    }
    else
    {
        /*
         * Create demuxer only if tiled display is disabled.
         */
        pipeline->demuxer =
                gst_element_factory_make (NVDS_ELEM_STREAM_DEMUX, "demuxer");
        if (!pipeline->demuxer) {
            NVGSTDS_ERR_MSG_V ("Failed to create element 'demuxer'");
            goto done;
        }
        gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->demuxer);

        for (i = 0; i < config->num_source_sub_bins; i++)
        {
            gchar pad_name[16];
            GstPad *demux_src_pad;

            /* Check if any sink has been configured to render/encode output for
           * source index `i`. The processing instance for that source will be
           * created only if atleast one sink has been configured as such.
           */
            if (!Deepstream_source_code::is_sink_available_for_source_id(config, i))
                continue;

            if (!Deepstream_source_code::create_processing_instance(appCtx, i))
            {
                goto done;
            }
            gst_bin_add(GST_BIN(pipeline->pipeline),
                        pipeline->instance_bins[i].bin);

            g_snprintf(pad_name, 16, "src_%02d", i);
            demux_src_pad = gst_element_get_request_pad(pipeline->demuxer, pad_name);
            NVGSTDS_LINK_ELEMENT_FULL(pipeline->demuxer, pad_name,
                                      pipeline->instance_bins[i].bin, "sink");
            gst_object_unref(demux_src_pad);

            NVGSTDS_ELEM_ADD_PROBE(latency_probe_id,
                                   //pipeline->instance_bins[i].sink_bin.sub_bins[0].sink, "sink",
                                   pipeline->instance_bins[i].sink_bin.sub_bins[0].sink, "sink",
                    latency_measurement_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
                    appCtx);
            latency_probe_id = latency_probe_id;
        }
        last_elem = pipeline->demuxer;
    }

    if (config->tiled_display_config.enable == NV_DS_TILED_DISPLAY_ENABLE) {
        fps_pad = gst_element_get_static_pad (pipeline->tiled_display_bin.bin, "sink");
    }
    else {
        fps_pad = gst_element_get_static_pad (pipeline->demuxer, "sink");
    }

    pipeline->common_elements.appCtx = appCtx;
    // Decide where in the pipeline the element should be added and add only if
    // enabled
    if (config->dsexample_config.enable) {
        // Create dsexample element bin and set properties
        if (!create_dsexample_bin (&config->dsexample_config,
                                   &pipeline->dsexample_bin)) {
            goto done;
        }
        // Add dsexample bin to instance bin
        gst_bin_add (GST_BIN (pipeline->pipeline), pipeline->dsexample_bin.bin);

        // Link this bin to the last element in the bin
        NVGSTDS_LINK_ELEMENT (pipeline->dsexample_bin.bin, last_elem);

        NVGSTDS_ELEM_ADD_PROBE (dsexample_probe_id,
                                pipeline->dsexample_bin.bin, "src",
                                /*Deepstream_source_code::*/this->dsexample_buf_probe, GST_PAD_PROBE_TYPE_BUFFER,
                                appCtx);
        // Set this bin as the last element
        last_elem = pipeline->dsexample_bin.bin;
    }
    // create and add common components to pipeline.
    if (!Deepstream_source_code::create_common_elements (config, pipeline, &tmp_elem1, &tmp_elem2,
                                                         bbox_generated_post_analytics_cb)) {
        goto done;
    }

    if(!Deepstream_source_code::add_and_link_broker_sink(appCtx)) {
        goto done;
    }

    if (tmp_elem2) {
        NVGSTDS_LINK_ELEMENT (tmp_elem2, last_elem);
        last_elem = tmp_elem1;
    }

    NVGSTDS_LINK_ELEMENT (pipeline->multi_src_bin.bin, last_elem);

    // enable performance measurement and add call back function to receive
    // performance data.
    if (config->enable_perf_measurement) {
        appCtx->perf_struct.context = appCtx;
        enable_perf_measurement (&appCtx->perf_struct, fps_pad,
                                 pipeline->multi_src_bin.num_bins,
                                 config->perf_measurement_interval_sec,
                                 config->multi_source_config[0].dewarper_config.num_surfaces_per_frame,
                perf_cb);
    }
    //gst_object_unref (fps_pad);

    NVGSTDS_ELEM_ADD_PROBE (latency_probe_id,
                            pipeline->instance_bins->sink_bin.sub_bins[0].sink, "sink",
            Deepstream_source_code::latency_measurement_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
            appCtx);
    latency_probe_id = latency_probe_id;

    //      if (config->num_message_consumers) {
    //        for (i = 0; i < config->num_message_consumers; i++) {
    //          appCtx->c2d_ctx[i] = start_cloud_to_device_messaging (
    //                                    &config->message_consumer_config[i], appCtx);
    //          if (appCtx->c2d_ctx[i] == NULL) {
    //            NVGSTDS_ERR_MSG_V ("Failed to create message consumer");
    //            goto done;
    //          }
    //        }
    //      }

    GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (appCtx->pipeline.pipeline),
                                       GST_DEBUG_GRAPH_SHOW_ALL, "ds-app-null");

    g_mutex_init (&appCtx->app_lock);
    g_cond_init (&appCtx->app_cond);
    g_mutex_init (&appCtx->latency_lock);

    ret = TRUE;
done:
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

void Deepstream_source_code::destroy_pipeline(AppCtx *appCtx)
{
    gint64 end_time;
    NvDsConfig *config = &appCtx->config;
    guint i;
    GstBus *bus = NULL;

    end_time = g_get_monotonic_time () + G_TIME_SPAN_SECOND;

    if (!appCtx)
        return;

    if (appCtx->pipeline.demuxer) {
        gst_pad_send_event (gst_element_get_static_pad (appCtx->pipeline.demuxer,
                                                        "sink"), gst_event_new_eos ());
    } else if (appCtx->pipeline.instance_bins[0].sink_bin.bin) {
        gst_pad_send_event (gst_element_get_static_pad (appCtx->
                                                        pipeline.instance_bins[0].sink_bin.bin, "sink"),
                gst_event_new_eos ());
    }

    g_usleep (100000);

    g_mutex_lock (&appCtx->app_lock);
    if (appCtx->pipeline.pipeline) {
        bus = gst_pipeline_get_bus (GST_PIPELINE (appCtx->pipeline.pipeline));

        while (TRUE) {
            GstMessage *message = gst_bus_pop (bus);
            if (message == NULL)
                break;
            else if (GST_MESSAGE_TYPE (message) == GST_MESSAGE_ERROR)
                Deepstream_source_code::bus_callback (bus, message, appCtx);
            else
                gst_message_unref (message);
        }
        gst_element_set_state (appCtx->pipeline.pipeline, GST_STATE_NULL);
    }
    g_cond_wait_until (&appCtx->app_cond, &appCtx->app_lock, end_time);
    g_mutex_unlock (&appCtx->app_lock);

    for (i = 0; i < appCtx->config.num_source_sub_bins; i++) {
        NvDsInstanceBin *bin = &appCtx->pipeline.instance_bins[i];
        if (config->osd_config.enable) {
            NVGSTDS_ELEM_REMOVE_PROBE (bin->all_bbox_buffer_probe_id,
                                       bin->osd_bin.nvosd, "sink");
        } else {
            NVGSTDS_ELEM_REMOVE_PROBE (bin->all_bbox_buffer_probe_id,
                                       bin->sink_bin.bin, "sink");
        }

        if (config->primary_gie_config.enable) {
            NVGSTDS_ELEM_REMOVE_PROBE (bin->primary_bbox_buffer_probe_id,
                                       bin->primary_gie_bin.bin, "src");
        }

    }
    if(appCtx->latency_info == NULL)
    {
        free(appCtx->latency_info);
        appCtx->latency_info = NULL;
    }

    g_mutex_clear(&appCtx->latency_lock);

    if (appCtx->pipeline.pipeline) {
        bus = gst_pipeline_get_bus (GST_PIPELINE (appCtx->pipeline.pipeline));
        gst_bus_remove_watch (bus);
        gst_object_unref (bus);
        gst_object_unref (appCtx->pipeline.pipeline);
    }
}

gboolean Deepstream_source_code::pause_pipeline(AppCtx *appCtx)
{
    GstState cur;
    GstState pending;
    GstStateChangeReturn ret;
    GstClockTime timeout = 5 * GST_SECOND / 1000;

    ret =
            gst_element_get_state (appCtx->pipeline.pipeline, &cur, &pending,
                                   timeout);

    if (ret == GST_STATE_CHANGE_ASYNC) {
        return FALSE;
    }

    if (cur == GST_STATE_PAUSED) {
        return TRUE;
    } else if (cur == GST_STATE_PLAYING) {
        gst_element_set_state (appCtx->pipeline.pipeline, GST_STATE_PAUSED);
        gst_element_get_state (appCtx->pipeline.pipeline, &cur, &pending,
                               GST_CLOCK_TIME_NONE);
        pause_perf_measurement (&appCtx->perf_struct);
        return TRUE;
    } else {
        return FALSE;
    }
}

gboolean Deepstream_source_code::resume_pipeline(AppCtx *appCtx)
{
    GstState cur;
    GstState pending;
    GstStateChangeReturn ret;
    GstClockTime timeout = 5 * GST_SECOND / 1000;

    ret =
            gst_element_get_state (appCtx->pipeline.pipeline, &cur, &pending,
                                   timeout);

    if (ret == GST_STATE_CHANGE_ASYNC) {
        return FALSE;
    }

    if (cur == GST_STATE_PLAYING) {
        return TRUE;
    } else if (cur == GST_STATE_PAUSED) {
        gst_element_set_state (appCtx->pipeline.pipeline, GST_STATE_PLAYING);
        gst_element_get_state (appCtx->pipeline.pipeline, &cur, &pending,
                               GST_CLOCK_TIME_NONE);
        resume_perf_measurement (&appCtx->perf_struct);
        return TRUE;
    } else {
        return FALSE;
    }
}

gboolean Deepstream_source_code::parse_tests(NvDsConfig *config, GKeyFile *key_file)
{
    gboolean ret = FALSE;
    gchar **keys = NULL;
    gchar **key = NULL;
    GError *error = NULL;

    keys = g_key_file_get_keys (key_file, CONFIG_GROUP_TESTS, NULL, &error);
    CHECK_ERROR (error);

    for (key = keys; *key; key++) {
        if (!g_strcmp0 (*key, CONFIG_GROUP_TESTS_FILE_LOOP)) {
            config->file_loop =
                    g_key_file_get_integer (key_file, CONFIG_GROUP_TESTS,
                                            CONFIG_GROUP_TESTS_FILE_LOOP, &error);
            CHECK_ERROR (error);
        } else {
            NVGSTDS_WARN_MSG_V ("Unknown key '%s' for group [%s]", *key,
                                CONFIG_GROUP_TESTS);
        }
    }

    ret = TRUE;
done:
    if (error) {
        g_error_free (error);
    }
    if (keys) {
        g_strfreev (keys);
    }
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

gboolean Deepstream_source_code::parse_app(NvDsConfig *config, GKeyFile *key_file, gchar *cfg_file_path)
{
    gboolean ret = FALSE;
    gchar **keys = NULL;
    gchar **key = NULL;
    GError *error = NULL;

    keys = g_key_file_get_keys (key_file, CONFIG_GROUP_APP, NULL, &error);
    CHECK_ERROR (error);

    for (key = keys; *key; key++) {
        if (!g_strcmp0 (*key, CONFIG_GROUP_APP_ENABLE_PERF_MEASUREMENT)) {
            config->enable_perf_measurement =
                    g_key_file_get_integer (key_file, CONFIG_GROUP_APP,
                                            CONFIG_GROUP_APP_ENABLE_PERF_MEASUREMENT, &error);
            CHECK_ERROR (error);
        } else if (!g_strcmp0 (*key, CONFIG_GROUP_APP_PERF_MEASUREMENT_INTERVAL)) {
            config->perf_measurement_interval_sec =
                    g_key_file_get_integer (key_file, CONFIG_GROUP_APP,
                                            CONFIG_GROUP_APP_PERF_MEASUREMENT_INTERVAL, &error);
            CHECK_ERROR (error);
        } else if (!g_strcmp0 (*key, CONFIG_GROUP_APP_GIE_OUTPUT_DIR)) {
            config->bbox_dir_path = get_absolute_file_path (cfg_file_path,
                                                            g_key_file_get_string (key_file, CONFIG_GROUP_APP,
                                                                                   CONFIG_GROUP_APP_GIE_OUTPUT_DIR, &error));
            CHECK_ERROR (error);
        } else if (!g_strcmp0 (*key, CONFIG_GROUP_APP_GIE_TRACK_OUTPUT_DIR)) {
            config->kitti_track_dir_path = get_absolute_file_path (cfg_file_path,
                                                                   g_key_file_get_string (key_file, CONFIG_GROUP_APP,
                                                                                          CONFIG_GROUP_APP_GIE_TRACK_OUTPUT_DIR, &error));
            CHECK_ERROR (error);
        } else {
            NVGSTDS_WARN_MSG_V ("Unknown key '%s' for group [%s]", *key,
                                CONFIG_GROUP_APP);
        }
    }

    ret = TRUE;
done:
    if (error) {
        g_error_free (error);
    }
    if (keys) {
        g_strfreev (keys);
    }
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

gboolean Deepstream_source_code::parse_source_list (NvDsConfig * config, GKeyFile * key_file,
                                                    gchar * cfg_file_path)
{
    gboolean ret = FALSE;
    gchar **keys = NULL;
    gchar **key = NULL;
    GError *error = NULL;
    gsize num_strings;

    keys = g_key_file_get_keys (key_file, CONFIG_GROUP_SOURCE_LIST, NULL, &error);
    CHECK_ERROR (error);

    for (key = keys; *key; key++) {
        if (!g_strcmp0 (*key, CONFIG_GROUP_SOURCE_LIST_NUM_SOURCE_BINS)) {
            config->total_num_sources =
                    g_key_file_get_integer (key_file, CONFIG_GROUP_SOURCE_LIST,
                                            CONFIG_GROUP_SOURCE_LIST_NUM_SOURCE_BINS, &error);
            CHECK_ERROR (error);
        } else if (!g_strcmp0 (*key, CONFIG_GROUP_SOURCE_LIST_URI_LIST)) {
            config->uri_list =
                    g_key_file_get_string_list (key_file, CONFIG_GROUP_SOURCE_LIST,
                                                CONFIG_GROUP_SOURCE_LIST_URI_LIST, &num_strings, &error);
            if (num_strings > MAX_SOURCE_BINS) {
                NVGSTDS_ERR_MSG_V ("App supports max %d sources", MAX_SOURCE_BINS);
                goto done;
            }
            CHECK_ERROR (error);
        } else {
            NVGSTDS_WARN_MSG_V ("Unknown key '%s' for group [%s]", *key,
                                CONFIG_GROUP_SOURCE_LIST);
        }
    }

    if (g_key_file_has_key (key_file, CONFIG_GROUP_SOURCE_LIST,
                            CONFIG_GROUP_SOURCE_LIST_URI_LIST, &error)) {
        if (g_key_file_has_key (key_file, CONFIG_GROUP_SOURCE_LIST,
                                CONFIG_GROUP_SOURCE_LIST_NUM_SOURCE_BINS, &error)) {
            if (num_strings != config->total_num_sources) {
                NVGSTDS_ERR_MSG_V ("Mismatch in URIs provided and num-source-bins.");
                goto done;
            }
        } else {
            config->total_num_sources = num_strings;
        }
    }

    ret = TRUE;
done:
    if (error) {
        g_error_free (error);
    }
    if (keys) {
        g_strfreev (keys);
    }
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

gboolean Deepstream_source_code::set_source_all_configs (NvDsConfig * config, gchar * cfg_file_path)
{
    guint i = 0;
    for (i = 0; i < config->total_num_sources; i++) {
        config->multi_source_config[i] = global_source_config;
        config->multi_source_config[i].camera_id = i;
        if (config->uri_list) {
            char *uri = config->uri_list[i];
            if (g_str_has_prefix (config->uri_list[i], "file://")) {
                config->multi_source_config[i].type = NV_DS_SOURCE_URI;
                config->multi_source_config[i].uri = g_strdup (uri + 7);
                config->multi_source_config[i].uri =
                        g_strdup_printf ("file://%s",
                                         get_absolute_file_path (cfg_file_path,
                                                                 config->multi_source_config[i].uri));
            } else if (g_str_has_prefix (config->uri_list[i], "rtsp://")) {
                config->multi_source_config[i].type = NV_DS_SOURCE_RTSP;
                config->multi_source_config[i].uri = config->uri_list[i];
            } else {
                gchar *source_id_start_ptr = uri + 4;
                gchar *source_id_end_ptr = NULL;
                long camera_id =
                        g_ascii_strtoull (source_id_start_ptr, &source_id_end_ptr, 10);
                if (source_id_start_ptr == source_id_end_ptr
                        || *source_id_end_ptr != '\0') {
                    NVGSTDS_ERR_MSG_V
                            ("Incorrect URI for camera source %s. FORMAT: <usb/csi>:<dev_node/sensor_id>",
                             uri);
                    return FALSE;
                }
                if (g_str_has_prefix (config->uri_list[i], "csi:")) {
                    config->multi_source_config[i].type = NV_DS_SOURCE_CAMERA_CSI;
                    config->multi_source_config[i].camera_csi_sensor_id = camera_id;
                } else if (g_str_has_prefix (config->uri_list[i], "usb:")) {
                    config->multi_source_config[i].type = NV_DS_SOURCE_CAMERA_V4L2;
                    config->multi_source_config[i].camera_v4l2_dev_node = camera_id;
                } else {
                    NVGSTDS_ERR_MSG_V ("URI %d (%s) not in proper format.", i,
                                       config->uri_list[i]);
                    return FALSE;
                }
            }
        }
    }
    return TRUE;
}


gboolean Deepstream_source_code::parse_config_file(NvDsConfig *config, gchar *cfg_file_path)
{
    GKeyFile *cfg_file = g_key_file_new ();
    GError *error = NULL;
    gboolean ret = FALSE;
    gchar **groups = NULL;
    gchar **group;
    guint i, j;

    config->source_list_enabled = FALSE;

    if (!APP_CFG_PARSER_CAT) {
        GST_DEBUG_CATEGORY_INIT (APP_CFG_PARSER_CAT, "NVDS_CFG_PARSER", 0, NULL);
    }

    if (!g_key_file_load_from_file (cfg_file, cfg_file_path, G_KEY_FILE_NONE,
                                    &error)) {
        GST_CAT_ERROR (APP_CFG_PARSER_CAT, "Failed to load uri file: %s",
                       error->message);
        goto done;
    }

    if (g_key_file_has_group (cfg_file, CONFIG_GROUP_SOURCE_LIST)) {
        if (!parse_source_list (config, cfg_file, cfg_file_path)) {
            GST_CAT_ERROR (APP_CFG_PARSER_CAT, "Failed to parse '%s' group",
                           CONFIG_GROUP_SOURCE_LIST);
            goto done;
        }
        config->num_source_sub_bins = config->total_num_sources;
        config->source_list_enabled = TRUE;
        if (!g_key_file_has_group (cfg_file, CONFIG_GROUP_SOURCE_ALL)) {
            NVGSTDS_ERR_MSG_V ("[source-attr-all] group not present.");
            ret = FALSE;
            goto done;
        }
        g_key_file_remove_group (cfg_file, CONFIG_GROUP_SOURCE_LIST, &error);
    }
    if (g_key_file_has_group (cfg_file, CONFIG_GROUP_SOURCE_ALL)) {
        if (!parse_source (&global_source_config,
                           cfg_file, CONFIG_GROUP_SOURCE_ALL, cfg_file_path)) {
            GST_CAT_ERROR (APP_CFG_PARSER_CAT, "Failed to parse '%s' group",
                           CONFIG_GROUP_SOURCE_LIST);
            goto done;
        }
        if (!set_source_all_configs (config, cfg_file_path)) {
            ret = FALSE;
            goto done;
        }
        g_key_file_remove_group (cfg_file, CONFIG_GROUP_SOURCE_ALL, &error);
    }

    groups = g_key_file_get_groups (cfg_file, NULL);
    for (group = groups; *group; group++) {
        gboolean parse_err = FALSE;
        GST_CAT_DEBUG (APP_CFG_PARSER_CAT, "Parsing group: %s", *group);
        if (!g_strcmp0 (*group, CONFIG_GROUP_APP)) {
            parse_err = !parse_app (config, cfg_file, cfg_file_path);
        }

        if (!strncmp (*group, CONFIG_GROUP_SOURCE,
                      sizeof (CONFIG_GROUP_SOURCE) - 1)) {
            if (config->num_source_sub_bins == MAX_SOURCE_BINS) {
                NVGSTDS_ERR_MSG_V ("App supports max %d sources", MAX_SOURCE_BINS);
                ret = FALSE;
                goto done;
            }
            gchar *source_id_start_ptr = *group + strlen (CONFIG_GROUP_SOURCE);
            gchar *source_id_end_ptr = NULL;
            guint index =
                    g_ascii_strtoull (source_id_start_ptr, &source_id_end_ptr, 10);
            if (source_id_start_ptr == source_id_end_ptr
                    || *source_id_end_ptr != '\0') {
                NVGSTDS_ERR_MSG_V
                        ("Source group \"[%s]\" is not in the form \"[source<%%d>]\"",
                         *group);
                ret = FALSE;
                goto done;
            }
            guint source_id = 0;
            if (config->source_list_enabled) {
                if (index >= config->total_num_sources) {
                    NVGSTDS_ERR_MSG_V
                            ("Invalid source group index %d, index cannot exceed %d", index,
                             config->total_num_sources);
                    ret = FALSE;
                    goto done;
                }
                source_id = index;
                NVGSTDS_INFO_MSG_V ("Some parameters to be overwritten for group [%s]",
                                    *group);
            } else {
                source_id = config->num_source_sub_bins;
            }
            parse_err = !parse_source (&config->multi_source_config[source_id],
                                       cfg_file, *group, cfg_file_path);
            if (config->source_list_enabled
                    && config->multi_source_config[source_id].type ==
                    NV_DS_SOURCE_URI_MULTIPLE) {
                NVGSTDS_ERR_MSG_V
                        ("MultiURI support not available if [source-list] is provided");
                ret = FALSE;
                goto done;
            }
            if (config->multi_source_config[source_id].enable
                    && !config->source_list_enabled) {
                config->num_source_sub_bins++;
            }
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_STREAMMUX)) {
            parse_err = !parse_streammux (&config->streammux_config, cfg_file, cfg_file_path);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_OSD)) {
            parse_err = !parse_osd (&config->osd_config, cfg_file);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_PRIMARY_GIE)) {
            parse_err =
                    !parse_gie (&config->primary_gie_config, cfg_file,
                                CONFIG_GROUP_PRIMARY_GIE, cfg_file_path);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_TRACKER)) {
            parse_err = !parse_tracker (&config->tracker_config, cfg_file, cfg_file_path);
        }

        if (!strncmp (*group, CONFIG_GROUP_SECONDARY_GIE,
                      sizeof (CONFIG_GROUP_SECONDARY_GIE) - 1)) {
            if (config->num_secondary_gie_sub_bins == MAX_SECONDARY_GIE_BINS) {
                NVGSTDS_ERR_MSG_V ("App supports max %d secondary GIEs", MAX_SECONDARY_GIE_BINS);
                ret = FALSE;
                goto done;
            }
            parse_err =
                    !parse_gie (&config->secondary_gie_sub_bin_config[config->
                    num_secondary_gie_sub_bins],
                    cfg_file, *group, cfg_file_path);
            if (config->secondary_gie_sub_bin_config[config->num_secondary_gie_sub_bins].enable){
                config->num_secondary_gie_sub_bins++;
            }
        }

        if (!strncmp (*group, CONFIG_GROUP_SINK, sizeof (CONFIG_GROUP_SINK) - 1)) {
            if (config->num_sink_sub_bins == MAX_SINK_BINS) {
                NVGSTDS_ERR_MSG_V ("App supports max %d sinks", MAX_SINK_BINS);
                ret = FALSE;
                goto done;
            }
            parse_err =
                    !parse_sink (&config->
                                 sink_bin_sub_bin_config[config->num_sink_sub_bins], cfg_file, *group,
                    cfg_file_path);
            if (config->
                    sink_bin_sub_bin_config[config->num_sink_sub_bins].enable){
                config->num_sink_sub_bins++;
            }
        }

        if (!strncmp (*group, CONFIG_GROUP_MSG_CONSUMER,
                      sizeof (CONFIG_GROUP_MSG_CONSUMER) - 1)) {
            if (config->num_message_consumers == MAX_MESSAGE_CONSUMERS) {
                NVGSTDS_ERR_MSG_V ("App supports max %d consumers", MAX_MESSAGE_CONSUMERS);
                ret = FALSE;
                goto done;
            }
            parse_err = !parse_msgconsumer (
                        &config->message_consumer_config[config->num_message_consumers],
                    cfg_file, *group, cfg_file_path);

            if (config->message_consumer_config[config->num_message_consumers].enable) {
                config->num_message_consumers++;
            }
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_TILED_DISPLAY)) {
            parse_err = !parse_tiled_display (&config->tiled_display_config, cfg_file);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_DSEXAMPLE)) {
            parse_err = !parse_dsexample (&config->dsexample_config, cfg_file);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_MSG_CONVERTER)) {
            parse_err = !parse_msgconv (&config->msg_conv_config, cfg_file, *group, cfg_file_path);
        }

        if (!g_strcmp0 (*group, CONFIG_GROUP_TESTS)) {
            parse_err = !parse_tests (config, cfg_file);
        }

        if (parse_err) {
            GST_CAT_ERROR (APP_CFG_PARSER_CAT, "Failed to parse '%s' group", *group);
            goto done;
        }
    }

    for (i = 0; i < config->num_secondary_gie_sub_bins; i++) {
        if (config->secondary_gie_sub_bin_config[i].unique_id ==
                config->primary_gie_config.unique_id) {
            NVGSTDS_ERR_MSG_V ("Non unique gie ids found");
            ret = FALSE;
            goto done;
        }
    }

    for (i = 0; i < config->num_secondary_gie_sub_bins; i++) {
        for (j = i + 1; j < config->num_secondary_gie_sub_bins; j++) {
            if (config->secondary_gie_sub_bin_config[i].unique_id ==
                    config->secondary_gie_sub_bin_config[j].unique_id) {
                NVGSTDS_ERR_MSG_V ("Non unique gie id %d found",
                                   config->secondary_gie_sub_bin_config[i].unique_id);
                ret = FALSE;
                goto done;
            }
        }
    }

    for (i = 0; i < config->num_source_sub_bins; i++) {
        if (config->multi_source_config[i].type == NV_DS_SOURCE_URI_MULTIPLE) {
            if (config->multi_source_config[i].num_sources < 1) {
                config->multi_source_config[i].num_sources = 1;
            }
            for (j = 1; j < config->multi_source_config[i].num_sources; j++) {
                if (config->num_source_sub_bins == MAX_SOURCE_BINS) {
                    NVGSTDS_ERR_MSG_V ("App supports max %d sources", MAX_SOURCE_BINS);
                    ret = FALSE;
                    goto done;
                }
                memcpy (&config->multi_source_config[config->num_source_sub_bins],
                        &config->multi_source_config[i],
                        sizeof (config->multi_source_config[i]));
                config->multi_source_config[config->num_source_sub_bins].type =
                        NV_DS_SOURCE_URI;
                config->multi_source_config[config->num_source_sub_bins].uri =
                        g_strdup_printf (config->multi_source_config[config->
                        num_source_sub_bins].uri, j);
                config->num_source_sub_bins++;
            }
            config->multi_source_config[i].type = NV_DS_SOURCE_URI;
            config->multi_source_config[i].uri =
                    g_strdup_printf (config->multi_source_config[i].uri, 0);
        }
    }
    ret = TRUE;

done:
    if (cfg_file) {
        g_key_file_free (cfg_file);
    }

    if (groups) {
        g_strfreev (groups);
    }

    if (error) {
        g_error_free (error);
    }
    if (!ret) {
        NVGSTDS_ERR_MSG_V ("%s failed", __func__);
    }
    return ret;
}

void Deepstream_source_code::all_bbox_generated(AppCtx *appCtx, GstBuffer *buf, NvDsBatchMeta *batch_meta, guint index)
{
    guint num_male = 0;
    guint num_female = 0;
    guint num_objects[128];

    memset (num_objects, 0, sizeof (num_objects));

    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {
        NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)l_frame->data;
        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {
            NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
            if (obj->unique_component_id ==
                    (gint) appCtx->config.primary_gie_config.unique_id) {
                if (obj->class_id >= 0 && obj->class_id < 128) {
                    num_objects[obj->class_id]++;
                }
                if (appCtx->person_class_id > -1
                        && obj->class_id == appCtx->person_class_id) {
                    if (strstr (obj->text_params.display_text, "Man")) {
                        str_replace (obj->text_params.display_text, "Man", "");
                        str_replace (obj->text_params.display_text, "Person", "Man");
                        num_male++;
                    } else if (strstr (obj->text_params.display_text, "Woman")) {
                        str_replace (obj->text_params.display_text, "Woman", "");
                        str_replace (obj->text_params.display_text, "Person", "Woman");
                        num_female++;
                    }
                }
            }
        }
    }
}

void Deepstream_source_code::_intr_handler(int signum)
{
    struct sigaction action;

    NVGSTDS_ERR_MSG_V ("User Interrupted.. \n");

    memset (&action, 0, sizeof (action));
    action.sa_handler = SIG_DFL;

    sigaction (SIGINT, &action, NULL);

    cintr = TRUE;
}

void Deepstream_source_code::perf_cb(gpointer context, NvDsAppPerfStruct *str)
{
    static guint header_print_cnt = 0;
    guint i;
    AppCtx *appCtx = (AppCtx *) context;
    guint numf = (num_instances == 1) ? str->num_instances : num_instances;

    g_mutex_lock (&fps_lock);
    if (num_instances > 1) {
        fps[appCtx->index] = str->fps[0];
        fps_avg[appCtx->index] = str->fps_avg[0];
    } else {
        for (i = 0; i < numf; i++) {
            fps[i] = str->fps[i];
            fps_avg[i] = str->fps_avg[i];
        }
    }

    num_fps_inst++;
    if (num_fps_inst < num_instances) {
        g_mutex_unlock (&fps_lock);
        return;
    }

    num_fps_inst = 0;

    if (header_print_cnt % 20 == 0) {
        g_print ("\n**PERF: ");
        for (i = 0; i < numf; i++) {
            g_print ("FPS %d (Avg)\t", i);
        }
        g_print ("\n");
        header_print_cnt = 0;
    }
    header_print_cnt++;
    g_print ("**PERF: \n");
    g_print("numf value is: %d\n",numf);
    for (i = 0; i < numf; i++) {
        g_print("i value is %d\n", i);
        g_print ("%.2f (%.2f)\n", fps[i], fps_avg[i]);

    }

    g_print ("\n");
    g_mutex_unlock (&fps_lock);
}

gboolean Deepstream_source_code::check_for_interrupt(gpointer data)
{
    if (quit) {
        return FALSE;
    }

    if (cintr) {
        cintr = FALSE;

        quit = TRUE;
        g_main_loop_quit (main_loop);

        return FALSE;
    }
    return TRUE;
}

void Deepstream_source_code::_intr_setup()
{
    struct sigaction action;

    memset (&action, 0, sizeof (action));
    action.sa_handler = Deepstream_source_code::_intr_handler;

    sigaction (SIGINT, &action, NULL);
}

gboolean Deepstream_source_code::kbhit()
{
    struct timeval tv;
    fd_set rdfs;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO (&rdfs);
    FD_SET (STDIN_FILENO, &rdfs);

    select (STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET (STDIN_FILENO, &rdfs);
}

void Deepstream_source_code::changemode(int dir)
{
    static struct termios oldt, newt;

    if (dir == 1) {
        tcgetattr (STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON);
        tcsetattr (STDIN_FILENO, TCSANOW, &newt);
    } else
        tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
}

void Deepstream_source_code::print_runtime_commands()
{
    g_print ("\nRuntime commands:\n"
             "\th: Print this help\n"
             "\tq: Quit\n\n" "\tp: Pause\n" "\tr: Resume\n\n");

    if (appCtx[0]->config.tiled_display_config.enable) {
        g_print
                ("NOTE: To expand a source in the 2D tiled display and view object details,"
                 " left-click on the source.\n"
                 "      To go back to the tiled display, right-click anywhere on the window.\n\n");
    }
}

static guint rrow, rcol;
static gboolean rrowsel = FALSE, selecting = FALSE;

gboolean Deepstream_source_code::event_thread_func(gpointer arg)
{
    guint i;
    gboolean ret = TRUE;

    // Check if all instances have quit
    for (i = 0; i < num_instances; i++) {
        if (!appCtx[i]->quit)
            break;
    }

    if (i == num_instances) {
        quit = TRUE;
        g_main_loop_quit (main_loop);
        return FALSE;
    }
    // Check for keyboard input
    if (!Deepstream_source_code::kbhit ()) {
        //continue;
        return TRUE;
    }
    int c = fgetc (stdin);
    g_print ("\n");

    gint source_id;
    GstElement *tiler = appCtx[0]->pipeline.tiled_display_bin.tiler;
    g_object_get (G_OBJECT (tiler), "show-source", &source_id, NULL);

    if (selecting) {
        if (rrowsel == FALSE) {
            if (c >= '0' && c <= '9') {
                rrow = c - '0';
                if (rrow < appCtx[0]->config.tiled_display_config.rows){
                    g_print ("--selecting source  row %d--\n", rrow);
                    rrowsel = TRUE;
                }else{
                    g_print ("--selected source  row %d out of bound, reenter\n", rrow);
                }
            }
        } else {
            if (c >= '0' && c <= '9') {
                unsigned int tile_num_columns = appCtx[0]->config.tiled_display_config.columns;
                rcol = c - '0';
                if (rcol < tile_num_columns){
                    selecting = FALSE;
                    rrowsel = FALSE;
                    source_id = tile_num_columns * rrow + rcol;
                    g_print ("--selecting source  col %d sou=%d--\n", rcol, source_id);
                    if (source_id >= (gint) appCtx[0]->config.num_source_sub_bins) {
                        source_id = -1;
                    } else {
                        source_ids[0] = source_id;
                        appCtx[0]->show_bbox_text = TRUE;
                        g_object_set (G_OBJECT (tiler), "show-source", source_id, NULL);
                    }
                }else{
                    g_print ("--selected source  col %d out of bound, reenter\n", rcol);
                }
            }
        }
    }
    switch (c) {
    case 'h':
        Deepstream_source_code::print_runtime_commands ();
        break;
    case 'p':
        for (i = 0; i < num_instances; i++){
            Deepstream_source_code dsc;
            dsc.pause_pipeline (appCtx[i]);
        }

        break;
    case 'r':
        for (i = 0; i < num_instances; i++){
            Deepstream_source_code dsc;
            dsc.resume_pipeline (appCtx[i]);
        }
        break;
    case 'q':
        quit = TRUE;
        g_main_loop_quit (main_loop);
        ret = FALSE;
        break;
    case 'z':
        if (source_id == -1 && selecting == FALSE) {
            g_print ("--selecting source --\n");
            selecting = TRUE;
        } else {
            if (!show_bbox_text)
                appCtx[0]->show_bbox_text = FALSE;
            g_object_set (G_OBJECT (tiler), "show-source", -1, NULL);
            source_ids[0] = -1;
            selecting = FALSE;
            g_print ("--tiled mode --\n");
        }
        break;
    default:
        break;
    }
    return ret;
}

int Deepstream_source_code::get_source_id_from_coordinates(float x_rel, float y_rel)
{
    int tile_num_rows = appCtx[0]->config.tiled_display_config.rows;
    int tile_num_columns = appCtx[0]->config.tiled_display_config.columns;

    int source_id = (int) (x_rel * tile_num_columns);
    source_id += ((int) (y_rel * tile_num_rows)) * tile_num_columns;

    /* Don't allow clicks on empty tiles. */
    if (source_id >= (gint) appCtx[0]->config.num_source_sub_bins)
        source_id = -1;

    return source_id;
}

gpointer Deepstream_source_code::nvds_x_event_thread(gpointer data)
{
    g_mutex_lock (&disp_lock);
    while (display) {
        XEvent e;
        guint index;
        while (XPending (display)) {
            XNextEvent (display, &e);
            switch (e.type) {
            case ButtonPress:
            {
                XWindowAttributes win_attr;
                XButtonEvent ev = e.xbutton;
                gint source_id;
                GstElement *tiler;

                XGetWindowAttributes (display, ev.window, &win_attr);

                for (index = 0; index < MAX_INSTANCES; index++)
                    if (ev.window == windows[index])
                        break;

                tiler = appCtx[index]->pipeline.tiled_display_bin.tiler;
                g_object_get (G_OBJECT (tiler), "show-source", &source_id, NULL);

                if (ev.button == Button1 && source_id == -1) {
                    source_id =
                            Deepstream_source_code::get_source_id_from_coordinates (ev.x * 1.0 / win_attr.width,
                                                                                    ev.y * 1.0 / win_attr.height);

                    //g_print("Source id in ds, left clicked %d\n", source_id);
                    MainWindow::setPositive_left_clicked_full_disp_blink();
                    if (source_id > -1) {
                        g_object_set (G_OBJECT (tiler), "show-source", source_id, NULL);
                        source_ids[index] = source_id;
                        appCtx[index]->show_bbox_text = FALSE;
                        //                        appCtx[index] = (AppCtx *)g_malloc0 (sizeof (AppCtx));
                        //                        appCtx[index]->show_bbox_text = TRUE;
                        //                        if (show_bbox_text) {

                        //                        }
                    }
                } else if (ev.button == Button3) {
                    MainWindow::setNegative_left_clicked_full_disp_blink();
                    g_object_set (G_OBJECT (tiler), "show-source", -1, NULL);
                    source_ids[index] = -1;
                    //g_print("Source id in ds, right clicked\n");
                    if (!show_bbox_text)
                        appCtx[index]->show_bbox_text = FALSE;
                }
            }
                break;
            case KeyRelease:
            case KeyPress:
            {
                KeySym p, r, q;
                guint i;
                p = XKeysymToKeycode (display, XK_P);
                r = XKeysymToKeycode (display, XK_R);
                q = XKeysymToKeycode (display, XK_Q);
                if (e.xkey.keycode == p) {
                    for (i = 0; i < num_instances; i++){
                        Deepstream_source_code dsc;
                        dsc.pause_pipeline (appCtx[i]);
                    }
                    break;
                }
                if (e.xkey.keycode == r) {
                    for (i = 0; i < num_instances; i++){
                        Deepstream_source_code dsc;
                        dsc.resume_pipeline (appCtx[i]);
                    }
                    break;
                }
                if (e.xkey.keycode == q) {
                    quit = TRUE;
                    g_main_loop_quit (main_loop);
                }
            }
                break;
            case ClientMessage:
            {
                Atom wm_delete;
                for (index = 0; index < MAX_INSTANCES; index++)
                    if (e.xclient.window == windows[index])
                        break;

                wm_delete = XInternAtom (display, "WM_DELETE_WINDOW", 1);
                if (wm_delete != None && wm_delete == (Atom) e.xclient.data.l[0]) {
                    quit = TRUE;
                    g_main_loop_quit (main_loop);
                }
            }
                break;
            }
        }
        g_mutex_unlock (&disp_lock);
        g_usleep (G_USEC_PER_SEC / 20);
        g_mutex_lock (&disp_lock);
    }
    g_mutex_unlock (&disp_lock);
    return NULL;
}

gboolean Deepstream_source_code::overlay_graphics(AppCtx *appCtx, GstBuffer *buf, NvDsBatchMeta *batch_meta, guint index)
{
    if (source_ids[index] == -1)
        return TRUE;

    NvDsFrameLatencyInfo *latency_info = NULL;
    NvDsDisplayMeta *display_meta =
            nvds_acquire_display_meta_from_pool (batch_meta);

    display_meta->num_labels = 1;
    display_meta->text_params[0].display_text = g_strdup_printf ("Source: %s",
                                                                 appCtx->config.multi_source_config[source_ids[index]].uri);

    display_meta->text_params[0].y_offset = 20;
    display_meta->text_params[0].x_offset = 20;
    //  display_meta->text_params[0].font_params.font_color = (NvOSD_ColorParams) {
    //  0, 1, 0, 1};
    display_meta->text_params[0].font_params.font_size =
            appCtx->config.osd_config.text_size * 1.5;
    display_meta->text_params[0].font_params.font_name = "Serif";
    display_meta->text_params[0].set_bg_clr = 1;
    //  display_meta->text_params[0].text_bg_clr = (NvOSD_ColorParams) {
    //  0, 0, 0, 1.0};


    if(nvds_enable_latency_measurement) {
        g_mutex_lock (&appCtx->latency_lock);
        latency_info = &appCtx->latency_info[index];
        display_meta->num_labels++;
        display_meta->text_params[1].display_text = g_strdup_printf ("Latency: %lf",
                                                                     latency_info->latency);
        g_mutex_unlock (&appCtx->latency_lock);

        display_meta->text_params[1].y_offset = (display_meta->text_params[0].y_offset * 2 )+
                display_meta->text_params[0].font_params.font_size;
        display_meta->text_params[1].x_offset = 20;
        //    display_meta->text_params[1].font_params.font_color = (NvOSD_ColorParams) {
        //      0, 1, 0, 1};
        display_meta->text_params[1].font_params.font_size =
                appCtx->config.osd_config.text_size * 1.5;
        display_meta->text_params[1].font_params.font_name = "Arial";
        display_meta->text_params[1].set_bg_clr = 1;
        //    display_meta->text_params[1].text_bg_clr = (NvOSD_ColorParams) {
        //      0, 0, 0, 1.0};
    }

    nvds_add_display_meta_to_frame (nvds_get_nth_frame_meta (batch_meta->
                                                             frame_meta_list, 0), display_meta);
    return TRUE;
}

GstPadProbeReturn Deepstream_source_code::dsexample_buf_probe(GstPad *pad, GstPadProbeInfo *info, gpointer u_data)
{
    GstBuffer *buf = (GstBuffer *) info->data;
    NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);

    AppCtx *appCtx = (AppCtx *) u_data;
    //qDebug()<<"dsexample_buf_probe start...";
    for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
         l_frame = l_frame->next) {

        NvDsFrameMeta *frame_meta = (NvDsFrameMeta*)l_frame->data;

        int source_id = (int) frame_meta->source_id;

        //qDebug() << "Strat of frame .................................> " << source_id;
        for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
             l_obj = l_obj->next) {

            NvDsObjectMeta * obj_meta = (NvDsObjectMeta *) (l_obj->data);

            if(obj_meta->class_id == 0){

                for (NvDsMetaList * p_obj = frame_meta->obj_meta_list; p_obj != NULL;
                     p_obj = p_obj->next){

                    NvDsObjectMeta *person_meta = (NvDsObjectMeta*) (p_obj->data);

                    NvDsBatchMeta *batch_meta_f = frame_meta->base_meta.batch_meta;
                    NvDsDisplayMeta *display_meta_disp = nvds_acquire_display_meta_from_pool(batch_meta_f);

                    if(person_meta->class_id == 0){

                        int pl = person_meta->rect_params.left;
                        int pt = person_meta->rect_params.top;
                        int pw = person_meta->rect_params.width;
                        int ph = person_meta->rect_params.height;

                        int fl = obj_meta->rect_params.left;
                        int ft = obj_meta->rect_params.top;
                        int fw = obj_meta->rect_params.width;
                        int fh = obj_meta->rect_params.height;



                        if((pl<=fl && pt<=ft) &&
                                ((pl+pw)>=(fl+fw) && pt<=ft) && (pl<=fl &&
                                                                 (pt+ph)>=(ft+fh)) && ((pl+pw)>=(fl+fw) && (pt+ph)>=(ft+fh))){

                            watchcam::rectangle rect(person_meta->rect_params.left,person_meta->rect_params.top,person_meta->rect_params.width,person_meta->rect_params.height);
                            rect.source_id = source_id;

                            //                            Buf_info::names_buf_info *buf = new Buf_info::names_buf_info();
                            //                            buf->source_id = source_id;

                            //                            Buf_info::names_buf_info *buf_in = new Buf_info::names_buf_info();
                            //                            buf_in->source_id = source_id;

                            for (NvDsMetaList * ap_obj = frame_meta->obj_meta_list; ap_obj != NULL;
                                 ap_obj = ap_obj->next){

                                NvDsObjectMeta *aperson_meta = (NvDsObjectMeta*) (ap_obj->data);

                                cv::Point p1(pl, pt);
                                cv::Point p2(aperson_meta->rect_params.left, aperson_meta->rect_params.top);
                                double res = (cv::norm(p1-p2))/64;

                                if(aperson_meta->class_id == 0 && (res<4 && res>3) &&
                                        aperson_meta->object_id != person_meta->object_id){

                                    cv::Mat *metadata_close_person = NULL;

                                    for (NvDsMetaList * p_user_meta = aperson_meta->obj_user_meta_list; p_user_meta != NULL;
                                         p_user_meta = p_user_meta->next){

                                        NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
                                        metadata_close_person = (cv::Mat*) user_metap->user_meta_data;

                                    }
                                    aperson_meta->rect_params.has_bg_color = 1;
                                    aperson_meta->rect_params.bg_color = (NvOSD_ColorParams) {1.0, 0.0, 0.0, 0.5};
                                    if(metadata_close_person != NULL  && metadata_close_person->rows>=0 && metadata_close_person->cols>=0
                                            /*&& metadata->rows<=32 && metadata->cols<=32*/){
                                        std::pair<cv::Mat*, float> per;
                                        per.first = metadata_close_person;
                                        per.second = res;

                                        //                                        buf->person_vec.push_back(per);
                                        //                                        buf_in->person_vec.push_back(per);
                                        //                                        metadata->deallocate();
                                        //                                        metadata->release();
                                        rect.person.push_back(per);
                                    }

                                }/*else{
                                    aperson_meta->rect_params.has_bg_color = 1;
                                    aperson_meta->rect_params.bg_color = (NvOSD_ColorParams) {0.0, 1.0, 0.0, 0.5};
                                }*/
                            }
                            cv::Mat *metadatap = NULL;cv::Mat *metadata  = NULL;

                            for (NvDsMetaList * p_user_meta = person_meta->obj_user_meta_list; p_user_meta != NULL;
                                 p_user_meta = p_user_meta->next){

                                NvDsUserMeta * user_metap = (NvDsUserMeta *) (p_user_meta->data);
                                metadatap = (cv::Mat*) user_metap->user_meta_data;
                            }
                            for (NvDsMetaList * f_user_meta = obj_meta->obj_user_meta_list; f_user_meta != NULL;
                                 f_user_meta = f_user_meta->next){

                                NvDsUserMeta * user_meta = (NvDsUserMeta *) (f_user_meta->data);
                                metadata = (cv::Mat*) user_meta->user_meta_data;

                                std::string person_color, mask_or_unmask;
                                person_color = "Unknown_color";
                                mask_or_unmask = "clear";

                                NvDsGieConfig *gie_config = NULL;

                                // mask or unmask
                                gie_config = &appCtx->config.secondary_gie_sub_bin_config[0];

                                if (6 == (gint) gie_config->unique_id){


                                    for (NvDsMetaList * l_class = obj_meta->classifier_meta_list; l_class != NULL;
                                         l_class = l_class->next) {
                                        //                                qDebug() << "9999999999999999999999999999999999999999";
                                        NvDsClassifierMeta *cmeta = (NvDsClassifierMeta *) l_class->data;
                                        for (NvDsMetaList * l_label = cmeta->label_info_list; l_label != NULL;
                                             l_label = l_label->next) {
                                            NvDsLabelInfo *label = (NvDsLabelInfo *) l_label->data;

                                            if (label->pResult_label) {
                                            }
                                            else if (label->result_label[0] != '\0') {
                                                gchar* str_color = NULL;
                                                str_color = g_strdup_printf("%s",label->result_label);
                                                if(QString::compare(str_color, "Obj_label") != 0){
                                                    qDebug() << "......................" << str_color;
                                                    mask_or_unmask = str_color;
                                                }
                                            }
                                        }
                                        break;
                                        gie_config = NULL;
                                    }
                                }
                                // color
                                gie_config = &appCtx->config.secondary_gie_sub_bin_config[0];

                                if (5 == (gint) gie_config->unique_id){


                                    for (NvDsMetaList * l_class = person_meta->classifier_meta_list; l_class != NULL;
                                         l_class = l_class->next) {
                                        //                                qDebug() << "9999999999999999999999999999999999999999";
                                        NvDsClassifierMeta *cmeta = (NvDsClassifierMeta *) l_class->data;
                                        for (NvDsMetaList * l_label = cmeta->label_info_list; l_label != NULL;
                                             l_label = l_label->next) {
                                            NvDsLabelInfo *label = (NvDsLabelInfo *) l_label->data;

                                            if (label->pResult_label) {
                                            }
                                            else if (label->result_label[0] != '\0') {
                                                gchar* str_color = NULL;
                                                str_color = g_strdup_printf("%s",label->result_label);
                                                if(QString::compare(str_color, "Obj_label") != 0){
                                                    //                                                    qDebug() << "......................" << str_color;
                                                    person_color = str_color;
                                                }
                                            }
                                        }
                                        break;
                                        gie_config = NULL;
                                    }
                                }


                                                       //qDebug() << "dhan start";

                                rect.mask_or_unmask = mask_or_unmask;
                                rect.str_color = person_color;
                                rect.fps = fps[0];

                                //                                buf->mask_status = mask_or_unmask;
                                //                                buf->color = person_color;
                                //                                buf->fps = fps[0];
                                //                                buf_in->mask_status = mask_or_unmask;
                                //                                buf_in->color = person_color;
                                //                                buf_in->fps = fps[0];

                                if(metadatap != NULL && metadata != NULL && metadatap->rows>=0 && metadatap->cols>=0
                                        && metadata->rows>=0 && metadata->cols>=0/*
                                                && metadata->rows<=32 && metadata->cols<=32
                                                && metadatap->rows<=32 && metadatap->cols<=32*/){
                                    //                                    buf_in->person = metadatap;
                                    //                                    buf_in->face = metadata;
                                    //                                    MainWindow::fromDsToMain(buf_in);
                                    //                                    metadatap->deallocate();
                                    //                                    metadatap->release();
                                    //                                    metadata->deallocate();
                                    //                                    metadata->release();

                                }
                                //                                delete buf_in;
                                //qDebug()<<"before fromdstomain call";
                                MainWindow::fromDsToMain(metadatap, metadata, rect);
                                //                                MainWindow::fromDsToMain(metadatap, metadata, buf);

                            }
                        }

                    }

                }
                break;
            }

        }
    }

    return GST_PAD_PROBE_OK;
}
