#ifndef DEEPSTREAM_SOURCE_CODE_H
#define DEEPSTREAM_SOURCE_CODE_H
#include<mainwindow.h>
#include <QObject>

#include <QDebug>
#include <QFile>
#include <QMutex>
#include "deepstream/deepstream_app.h"
#include "DS_sources/apps/apps-common/includes/deepstream_config_file_parser.h"
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
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <nvdstracker.h>
#include "rectangle.h"
#include "nvds_analytics_meta.h"


#define MAX_INSTANCES 128
//#define APP_TITLE "WatchCam"

//#define DEFAULT_X_WINDOW_WIDTH 1920
//#define DEFAULT_X_WINDOW_HEIGHT 1080
#define MAX_INSTANCES 128
//#define APP_TITLE "WATCHCAM"
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
#define CEIL(a,b) ((a + b - 1) / b)
#define SOURCE_RESET_INTERVAL_IN_MS 60000
#define FPS_PRINT_INTERVAL 300

// add new header file
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <math.h>
//#include <string>
//#include <typeinfo>
//#include <iostream>
//#include <QMutex>
//#include <QThread>
//#include <QDebug>
//#include <QPixmap>
//#include <vector>
//#include <utility>

//#include "AI_src/network.h"
//#include "AI_src/region_layer.h"
//#include "AI_src/cost_layer.h"
//#include "AI_src/utils.h"

//#include "AI_src/parser.h"
//#include "AI_src/box.h"
//#include "AI_src/demo.h"
//#include "AI_src/option_list.h"
//#include "AI_src/blas.h"

//#include "AI_src/cuda.h"
//#include "person.h"
#include "rectangle.h"
//#include "tracking.h"
////#include <cairo/cairo.h>
//#include <string.h>
//#include <QtConcurrent>
//#include "worker.h"

//#include <gst/gst.h>
//#include <gst/app/gstappsink.h>
//#include <glib.h>
//#include <math.h>
//#include <string.h>
//#include <sys/time.h>
//#include <deque>
//#include "gstnvdsmeta.h"
////#include "gstnvstreammeta.h"
////#ifndef PLATFORM_TEGRA
//#include "gst-nvmessage.h"
////#endif
////#include "gst-nvmessage.h"
//using namespace cv;
//// end of header file
///
///
#include <names_buf_info.h>
using namespace Buf_info;

class Deepstream_source_code : public QObject
{
    Q_OBJECT

private:
//    int wi;
//    int he;
    int camera_index;
    std::vector<watchcam::rectangle > prev_frame;
    std::vector<int> live_tracking_id;
    //static double fp_first_index;
//    void draw_detections_with_FR(image im, image orig, int num, float thresh, box *boxes, float **probs, char **names, image **alphabet, int classes,
//                                     std::vector<watchcam::rectangle > &rects);



public:

    explicit Deepstream_source_code(QObject *parent = nullptr/*, int w, int h*/);
    void constructorDeepStream();
    static gboolean add_and_link_broker_sink (AppCtx * appCtx);
    static gboolean is_sink_available_for_source_id(NvDsConfig *config, guint source_id);
    static gboolean watch_source_status (gpointer data);
    static gboolean bus_callback (GstBus * bus, GstMessage * message, gpointer data);
    static GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * msg, gpointer data);
    static void write_kitti_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static void write_kitti_track_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static gint component_id_compare_func (gconstpointer a, gconstpointer b);
    static void process_meta_test (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static void process_meta (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static void process_buffer (GstBuffer * buf, AppCtx * appCtx, guint index);
    static GstPadProbeReturn gie_primary_processing_done_buf_prob (GstPad * pad, GstPadProbeInfo * info,
                                                                   gpointer u_data);
    static GstPadProbeReturn gie_processing_done_buf_prob (GstPad * pad, GstPadProbeInfo * info,
                                                           gpointer u_data);
    static GstPadProbeReturn analytics_done_buf_prob (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
    static GstPadProbeReturn latency_measurement_buf_prob(GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
    static gboolean create_processing_instance (AppCtx * appCtx, guint index);
    static gboolean create_common_elements (NvDsConfig * config, NvDsPipeline * pipeline,
                                            GstElement ** sink_elem, GstElement ** src_elem,
                                            bbox_generated_callback bbox_generated_post_analytics_cb);
    gboolean create_pipeline (AppCtx * appCtx,
                              bbox_generated_callback bbox_generated_post_analytics_cb,
                              bbox_generated_callback all_bbox_generated_cb, perf_callback perf_cb,
                              overlay_graphics_callback overlay_graphics_cb);
    void destroy_pipeline (AppCtx * appCtx);
    gboolean pause_pipeline (AppCtx * appCtx);
    gboolean resume_pipeline (AppCtx * appCtx);
    static gboolean parse_tests (NvDsConfig *config, GKeyFile *key_file);
    static gboolean parse_app (NvDsConfig *config, GKeyFile *key_file, gchar *cfg_file_path);
    gboolean parse_config_file (NvDsConfig *config, gchar *cfg_file_path);
    static void all_bbox_generated (AppCtx * appCtx, GstBuffer * buf,
                                    NvDsBatchMeta * batch_meta, guint index);
    static void _intr_handler (int signum);
    static void perf_cb (gpointer context, NvDsAppPerfStruct * str);
    static gboolean check_for_interrupt (gpointer data);
    static void _intr_setup (void);
    static gboolean kbhit (void);
    static void changemode (int dir);
    static void print_runtime_commands (void);
    static gboolean event_thread_func (gpointer arg);
    static int get_source_id_from_coordinates (float x_rel, float y_rel);
    static gpointer nvds_x_event_thread (gpointer data);
    static gboolean overlay_graphics (AppCtx * appCtx, GstBuffer * buf,
                                      NvDsBatchMeta * batch_meta, guint index);
    static GstPadProbeReturn dsexample_buf_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
    Display *disToMain;
    Window singleWin;
    static gboolean create_demux_pipeline (AppCtx * appCtx, guint index);
    gboolean parse_source_list (NvDsConfig * config, GKeyFile * key_file,
        gchar * cfg_file_path);
    static gboolean set_source_all_configs (NvDsConfig * config, gchar * cfg_file_path);
    static GstPadProbeReturn demux_latency_measurement_buf_prob (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);
    // display row and column
    int num_of_rows;
    int num_of_columns;
    static GstPadProbeReturn nvdsanalytics_src_pad_buffer_probe (GstPad * pad, GstPadProbeInfo * info, gpointer u_data);

    static void coordinatesOfFrame(int rrows, int ccolumns, int w, int h, QList<float> divisible, AppCtx *appCtx);



signals:
    void sendDisToMainFromDssc(Display*);
    void setDispRowColumn(int, int);

public slots:
    void startDeepStream();
    static void gotDivisorValue(std::vector<std::pair<int, double>>);
//    std::vector<int> getSourceVecInSettings();
};

#endif // DEEPSTREAM_SOURCE_CODE_H
