#ifndef DS_SOURCE_CODE_H
#define DS_SOURCE_CODE_H

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
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


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

class DS_source_code
{



public:
    DS_source_code();
    static gboolean add_and_link_broker_sink (AppCtx * appCtx);
    static gboolean is_sink_available_for_source_id(NvDsConfig *config, guint source_id);
    static gboolean watch_source_status (gpointer data);
    static gboolean bus_callback (GstBus * bus, GstMessage * message, gpointer data);
    static GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * msg, gpointer data);
    static void write_kitti_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static void write_kitti_track_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta);
    static gint component_id_compare_func (gconstpointer a, gconstpointer b);
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

};

#endif // DS_SOURCE_CODE_H
