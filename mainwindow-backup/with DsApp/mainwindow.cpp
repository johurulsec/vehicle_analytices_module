#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <dialogs/settingsdialog.h>

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

#define MAX_INSTANCES 128
#define APP_TITLE "DeepStream"

#define DEFAULT_X_WINDOW_WIDTH 1920
#define DEFAULT_X_WINDOW_HEIGHT 1080

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

#define MAX_INSTANCES 128
#define APP_TITLE "DeepStream"

#define DEFAULT_X_WINDOW_WIDTH 1920
#define DEFAULT_X_WINDOW_HEIGHT 1080

AppCtx *appCtx[MAX_INSTANCES];
static guint cintr = FALSE;
static GMainLoop *main_loop = NULL;
static gchar **cfg_files = NULL;//"/home/sigmind/deepstream_sdk_v4.0_jetson/sources/apps/sample_apps/deepstream-app/source30_1080p_dec_infer-resnet_tiled_display_int8.txt";
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

#include <string.h>
#include "deepstream/deepstream_app.h"
#include "deepstream_config_file_parser.h"

#define CONFIG_GROUP_APP "application"
#define CONFIG_GROUP_APP_ENABLE_PERF_MEASUREMENT "enable-perf-measurement"
#define CONFIG_GROUP_APP_PERF_MEASUREMENT_INTERVAL "perf-measurement-interval-sec"
#define CONFIG_GROUP_APP_GIE_OUTPUT_DIR "gie-kitti-output-dir"
#define CONFIG_GROUP_APP_GIE_TRACK_OUTPUT_DIR "kitti-track-output-dir"

#define CONFIG_GROUP_TESTS "tests"
#define CONFIG_GROUP_TESTS_FILE_LOOP "file-loop"

GST_DEBUG_CATEGORY_EXTERN (APP_CFG_PARSER_CAT);


#define CHECK_ERROR(error) \
    if (error) { \
        GST_CAT_ERROR (APP_CFG_PARSER_CAT, "%s", error->message); \
        goto done; \
    }






#include <gst/gst.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "deepstream/deepstream_app.h"

#define MAX_DISPLAY_LEN 64
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
static gboolean
watch_source_status (gpointer data)
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

/**
 * callback function to receive messages from components
 * in the pipeline.
 */
static gboolean
bus_callback (GstBus * bus, GstMessage * message, gpointer data)
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
      for (i = 0; i < bin->num_bins; i++) {
        if (bin->sub_bins[i].src_elem == (GstElement *) GST_MESSAGE_SRC (message))
          break;
      }

      if ((i != bin->num_bins) &&
          (appCtx->config.multi_source_config[0].type == NV_DS_SOURCE_RTSP)) {
        // Error from one of RTSP source.
        NvDsSrcBin *subBin = &bin->sub_bins[i];

        if (!subBin->reconfiguring ||
            g_strrstr(debuginfo, "500 (Internal Server Error)")) {
          if (!subBin->reconfiguring) {
            // Check status of stream at regular interval.
            g_timeout_add (SOURCE_RESET_INTERVAL_IN_MS,
                           watch_source_status, subBin);
          }
          // Reconfigure the stream.
          subBin->reconfiguring = TRUE;
          g_timeout_add (20, reset_source_pipeline, subBin);
        }
        g_error_free (error);
        g_free (debuginfo);
        return TRUE;
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

static GstBusSyncReply
bus_sync_handler (GstBus * bus, GstMessage * msg, gpointer data)
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

/**
 * Function to dump bounding box data in kitti format. For this to work,
 * property "gie-kitti-output-dir" must be set in configuration file.
 * Data of different sources and frames is dumped in separate file.
 */
static void
write_kitti_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta)
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

/**
 * Function to dump bounding box data in kitti format with tracking ID added.
 * For this to work, property "kitti-track-output-dir" must be set in configuration file.
 * Data of different sources and frames is dumped in separate file.
 */
static void
write_kitti_track_output (AppCtx * appCtx, NvDsBatchMeta * batch_meta)
{
  gchar bbox_file[1024] = { 0 };
  FILE *bbox_params_dump_file = NULL;

  if (!appCtx->config.kitti_track_dir_path)
    return;

  for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
      l_frame = l_frame->next) {
    NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)l_frame->data;
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

static gint
component_id_compare_func (gconstpointer a, gconstpointer b)
{
  NvDsClassifierMeta *cmetaa = (NvDsClassifierMeta *) a;
  NvDsClassifierMeta *cmetab = (NvDsClassifierMeta *) b;

  if (cmetaa->unique_component_id < cmetab->unique_component_id)
    //return -1;
  if (cmetaa->unique_component_id > cmetab->unique_component_id)
    return 1;
  //return 0;
}

/**
 * Function to process the attached metadata. This is just for demonstration
 * and can be removed if not required.
 * Here it demonstrates to use bounding boxes of different color and size for
 * different type / class of objects.
 * It also demonstrates how to join the different labels(PGIE + SGIEs)
 * of an object to form a single string.
 */
static void
process_meta (AppCtx * appCtx, NvDsBatchMeta * batch_meta)
{
  // For single source always display text either with demuxer or with tiler
  if (!appCtx->config.tiled_display_config.enable ||
      appCtx->config.num_source_sub_bins == 1) {
    appCtx->show_bbox_text = 1;
  }

  for (NvDsMetaList * l_frame = batch_meta->frame_meta_list; l_frame != NULL;
      l_frame = l_frame->next) {
    NvDsFrameMeta *frame_meta = (NvDsFrameMeta *)l_frame->data;
    for (NvDsMetaList * l_obj = frame_meta->obj_meta_list; l_obj != NULL;
        l_obj = l_obj->next) {
      NvDsObjectMeta *obj = (NvDsObjectMeta *) l_obj->data;
      gint class_index = obj->class_id;
      NvDsGieConfig *gie_config = NULL;
      gchar *str_ins_pos = NULL;

      if (obj->unique_component_id ==
          (gint) appCtx->config.primary_gie_config.unique_id) {
        gie_config = &appCtx->config.primary_gie_config;
      } else {
        for (gint i = 0; i < (gint) appCtx->config.num_secondary_gie_sub_bins;
            i++) {
          gie_config = &appCtx->config.secondary_gie_sub_bin_config[i];
          if (obj->unique_component_id == (gint) gie_config->unique_id) {
            break;
          }
          gie_config = NULL;
        }
      }
      g_free (obj->text_params.display_text);
      obj->text_params.display_text = NULL;

      if (gie_config != NULL) {
        if (g_hash_table_contains (gie_config->bbox_border_color_table,
                class_index + (gchar *) NULL)) {
          obj->rect_params.border_color =
              *((NvOSD_ColorParams *)
              g_hash_table_lookup (gie_config->bbox_border_color_table,
                  class_index + (gchar *) NULL));
        } else {
          obj->rect_params.border_color = gie_config->bbox_border_color;
        }
        obj->rect_params.border_width = appCtx->config.osd_config.border_width;

        if (g_hash_table_contains (gie_config->bbox_bg_color_table,
                class_index + (gchar *) NULL)) {
          obj->rect_params.has_bg_color = 1;
          obj->rect_params.bg_color =
              *((NvOSD_ColorParams *)
              g_hash_table_lookup (gie_config->bbox_bg_color_table,
                  class_index + (gchar *) NULL));
        } else {
          obj->rect_params.has_bg_color = 0;
        }
      }

      if (!appCtx->show_bbox_text)
        continue;

      obj->text_params.x_offset = obj->rect_params.left;
      obj->text_params.y_offset = obj->rect_params.top - 30;
      obj->text_params.font_params.font_color =
          appCtx->config.osd_config.text_color;
      obj->text_params.font_params.font_size =
          appCtx->config.osd_config.text_size;
      obj->text_params.font_params.font_name = appCtx->config.osd_config.font;
      if (appCtx->config.osd_config.text_has_bg) {
        obj->text_params.set_bg_clr = 1;
        obj->text_params.text_bg_clr = appCtx->config.osd_config.text_bg_color;
      }

//      obj->text_params.display_text = g_malloc (128);
//      obj->text_params.display_text[0] = '\0';
//      str_ins_pos = obj->text_params.display_text;

      if (obj->obj_label[0] != '\0')
        sprintf (str_ins_pos, "%s", obj->obj_label);
      str_ins_pos += strlen (str_ins_pos);

      if (obj->object_id != UNTRACKED_OBJECT_ID) {
        sprintf (str_ins_pos, " %lu", obj->object_id);
        str_ins_pos += strlen (str_ins_pos);
      }

      obj->classifier_meta_list =
          g_list_sort (obj->classifier_meta_list, component_id_compare_func);
      for (NvDsMetaList * l_class = obj->classifier_meta_list; l_class != NULL;
          l_class = l_class->next) {
        NvDsClassifierMeta *cmeta = (NvDsClassifierMeta *) l_class->data;
        for (NvDsMetaList * l_label = cmeta->label_info_list; l_label != NULL;
            l_label = l_label->next) {
          NvDsLabelInfo *label = (NvDsLabelInfo *) l_label->data;
          if (label->pResult_label) {
            sprintf (str_ins_pos, " %s", label->pResult_label);
          } else if (label->result_label[0] != '\0') {
            sprintf (str_ins_pos, " %s", label->result_label);
          }
          str_ins_pos += strlen (str_ins_pos);
        }

      }
    }
  }
}

/**
 * Function which processes the inferred buffer and its metadata.
 * It also gives opportunity to attach application specific
 * metadata (e.g. clock, analytics output etc.).
 */
static void
process_buffer (GstBuffer * buf, AppCtx * appCtx, guint index)
{
  NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
  if (!batch_meta) {
    NVGSTDS_WARN_MSG_V ("Batch meta not found for buffer %p", buf);
    return;
  }
  process_meta (appCtx, batch_meta);
  //NvDsInstanceData *data = &appCtx->instance_data[index];
  //guint i;

  //  data->frame_num++;

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

/**
 * Buffer probe function to get the results of primary infer.
 * Here it demonstrates the use by dumping bounding box coordinates in
 * kitti format.
 */
static GstPadProbeReturn
gie_primary_processing_done_buf_prob (GstPad * pad, GstPadProbeInfo * info,
    gpointer u_data)
{
  GstBuffer *buf = (GstBuffer *) info->data;
  AppCtx *appCtx = (AppCtx *) u_data;
  NvDsBatchMeta *batch_meta = gst_buffer_get_nvds_batch_meta (buf);
  if (!batch_meta) {
    NVGSTDS_WARN_MSG_V ("Batch meta not found for buffer %p", buf);
    return GST_PAD_PROBE_OK;
  }

  write_kitti_output (appCtx, batch_meta);

  return GST_PAD_PROBE_OK;
}

/**
 * Probe function to get results after all inferences(Primary + Secondary)
 * are done. This will be just before OSD or sink (in case OSD is disabled).
 */
static GstPadProbeReturn
gie_processing_done_buf_prob (GstPad * pad, GstPadProbeInfo * info,
    gpointer u_data)
{
  GstBuffer *buf = (GstBuffer *) info->data;
  NvDsInstanceBin *bin = (NvDsInstanceBin *) u_data;
  guint index = bin->index;
  AppCtx *appCtx = bin->appCtx;

  if (gst_buffer_is_writable (buf))
    process_buffer (buf, appCtx, index);
  return GST_PAD_PROBE_OK;
}

/**
 * Buffer probe function after tracker.
 */
static GstPadProbeReturn
tracking_done_buf_prob (GstPad * pad, GstPadProbeInfo * info, gpointer u_data)
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
  write_kitti_track_output(appCtx, batch_meta);

  if (appCtx->primary_bbox_generated_cb)
    appCtx->primary_bbox_generated_cb (appCtx, buf, batch_meta, index);
  return GST_PAD_PROBE_OK;
}

static GstPadProbeReturn
latency_measurement_buf_prob(GstPad * pad, GstPadProbeInfo * info, gpointer u_data)
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

/**
 * Function to add components to pipeline which are dependent on number
 * of streams. These components work on single buffer. If tiling is being
 * used then single instance will be created otherwise < N > such instances
 * will be created for < N > streams
 */
static gboolean
create_processing_instance (AppCtx * appCtx, guint index)
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
        gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
  } else {
    NVGSTDS_ELEM_ADD_PROBE (instance_bin->all_bbox_buffer_probe_id,
        instance_bin->sink_bin.bin, "sink",
        gie_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER, instance_bin);
  }

  ret = TRUE;
done:
  if (!ret) {
    NVGSTDS_ERR_MSG_V ("%s failed", __func__);
  }
  return ret;
}

/**
 * Function to create common elements(Primary infer, tracker, secondary infer)
 * of the pipeline. These components operate on muxed data from all the
 * streams. So they are independent of number of streams in the pipeline.
 */
static gboolean
create_common_elements (NvDsConfig * config, NvDsPipeline * pipeline,
    GstElement ** sink_elem, GstElement ** src_elem,
    bbox_generated_callback primary_bbox_generated_cb)
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
        gie_primary_processing_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
        pipeline->common_elements.appCtx);
  }

  if (config->primary_gie_config.enable) {
    if (config->tracker_config.enable) {
      NVGSTDS_ELEM_ADD_PROBE (pipeline->common_elements.
          primary_bbox_buffer_probe_id,
          pipeline->common_elements.tracker_bin.bin, "src",
          tracking_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
          &pipeline->common_elements);
    } else {
      NVGSTDS_ELEM_ADD_PROBE (pipeline->common_elements.
          primary_bbox_buffer_probe_id,
          pipeline->common_elements.primary_gie_bin.bin, "src",
          tracking_done_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
          &pipeline->common_elements);
    }
  }
  ret = TRUE;
done:
  return ret;
}

/**
 * Main function to create the pipeline.
 */
gboolean
create_pipeline (AppCtx * appCtx,
    bbox_generated_callback primary_bbox_generated_cb,
    bbox_generated_callback all_bbox_generated_cb, perf_callback perf_cb,
    overlay_graphics_callback overlay_graphics_cb)
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

  _dsmeta_quark = g_quark_from_static_string (NVDS_META_STRING);

  appCtx->all_bbox_generated_cb = all_bbox_generated_cb;
  appCtx->primary_bbox_generated_cb = primary_bbox_generated_cb;
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
  pipeline->bus_id = gst_bus_add_watch (bus, bus_callback, appCtx);
  gst_bus_set_sync_handler (bus, bus_sync_handler, appCtx, NULL);
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
  } else {

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

    for (i = 0; i < config->num_source_sub_bins; i++) {
      gchar pad_name[16];
      gboolean create_instance = FALSE;
      GstPad *demux_src_pad;
      guint j;

      /* Check if any sink has been configured to render/encode output for
       * source index `i`. The processing instance for that source will be
       * created only if atleast one sink has been configured as such.
       */
      for (j = 0; j < config->num_sink_sub_bins; j++) {
        if (config->sink_bin_sub_bin_config[j].enable &&
            config->sink_bin_sub_bin_config[j].source_id == i) {
          create_instance = TRUE;
          break;
        }
      }

      if (!create_instance)
        continue;

      if (!create_processing_instance (appCtx, i)) {
        goto done;
      }
      gst_bin_add (GST_BIN (pipeline->pipeline),
          pipeline->instance_bins[i].bin);

      g_snprintf (pad_name, 16, "src_%02d", i);
      demux_src_pad = gst_element_get_request_pad (pipeline->demuxer, pad_name);
      NVGSTDS_LINK_ELEMENT_FULL (pipeline->demuxer, pad_name,
          pipeline->instance_bins[i].bin, "sink");
      gst_object_unref (demux_src_pad);
    }

    last_elem = pipeline->demuxer;
  }
  fps_pad = gst_element_get_static_pad (last_elem, "sink");

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

    // Set this bin as the last element
    last_elem = pipeline->dsexample_bin.bin;
  }
  // create and add common components to pipeline.
  if (!create_common_elements (config, pipeline, &tmp_elem1, &tmp_elem2,
          primary_bbox_generated_cb)) {
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
        config->perf_measurement_interval_sec, perf_cb);
  }
  //gst_object_unref (fps_pad);

  NVGSTDS_ELEM_ADD_PROBE (latency_probe_id,
      pipeline->instance_bins->sink_bin.sub_bins[0].sink, "sink",
      latency_measurement_buf_prob, GST_PAD_PROBE_TYPE_BUFFER,
      appCtx);
  latency_probe_id = latency_probe_id;

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

/**
 * Function to destroy pipeline and release the resources, probes etc.
 */
void
destroy_pipeline (AppCtx * appCtx)
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
        bus_callback (bus, message, appCtx);
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

gboolean
pause_pipeline (AppCtx * appCtx)
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

gboolean
resume_pipeline (AppCtx * appCtx)
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

static gboolean
parse_tests (NvDsConfig *config, GKeyFile *key_file)
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


static gboolean
parse_app (NvDsConfig *config, GKeyFile *key_file, gchar *cfg_file_path)
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


gboolean
parse_config_file (NvDsConfig *config, gchar *cfg_file_path)
{


  GKeyFile *cfg_file = g_key_file_new ();
  GError *error = NULL;
  gboolean ret = FALSE;
  gchar **groups = NULL;
  gchar **group;
  guint i, j;

 // cfg_file_path = '/home/sigmind/deepstream_sdk_v4.0_jetson/sources/apps/sample_apps/deepstream-app/source30_1080p_dec_infer-resnet_tiled_display_int8.txt';

  if (!APP_CFG_PARSER_CAT) {
    GST_DEBUG_CATEGORY_INIT (APP_CFG_PARSER_CAT, "NVDS_CFG_PARSER", 0, NULL);
  }

  if (!g_key_file_load_from_file (cfg_file, cfg_file_path, G_KEY_FILE_NONE,
          &error)) {
    GST_CAT_ERROR (APP_CFG_PARSER_CAT, "Failed to load uri file: %s",
        error->message);
    goto done;
  }
  groups = g_key_file_get_groups (cfg_file, NULL);

  for (group = groups; *group; group++) {
    gboolean parse_err = FALSE;
    GST_CAT_DEBUG (APP_CFG_PARSER_CAT, "Parsing group: %s", *group);
    if (!g_strcmp0 (*group, CONFIG_GROUP_APP)) {
      parse_err = !parse_app (config, cfg_file, cfg_file_path);
    }

    if (!strncmp (*group, CONFIG_GROUP_SOURCE, sizeof (CONFIG_GROUP_SOURCE) - 1)) {
      if (config->num_source_sub_bins == MAX_SOURCE_BINS) {
        NVGSTDS_ERR_MSG_V ("App supports max %d sources", MAX_SOURCE_BINS);
        ret = FALSE;
        goto done;
      }
      parse_err = !parse_source (&config->multi_source_config[config->num_source_sub_bins],
                                 cfg_file, *group, cfg_file_path);
      if (config->multi_source_config[config->num_source_sub_bins].enable) {
        config->num_source_sub_bins++;
      }
    }

    if (!g_strcmp0 (*group, CONFIG_GROUP_STREAMMUX)) {
      parse_err = !parse_streammux (&config->streammux_config, cfg_file);
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
          sink_bin_sub_bin_config[config->num_sink_sub_bins], cfg_file, *group);
      if (config->
          sink_bin_sub_bin_config[config->num_sink_sub_bins].enable){
        config->num_sink_sub_bins++;
      }
    }

    if (!g_strcmp0 (*group, CONFIG_GROUP_TILED_DISPLAY)) {
      parse_err = !parse_tiled_display (&config->tiled_display_config, cfg_file);
    }

    if (!g_strcmp0 (*group, CONFIG_GROUP_DSEXAMPLE)) {
      parse_err = !parse_dsexample (&config->dsexample_config, cfg_file);
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
        config->multi_source_config[config->num_source_sub_bins].type = NV_DS_SOURCE_URI;
        config->multi_source_config[config->num_source_sub_bins].uri =
          g_strdup_printf (config->multi_source_config[config->num_source_sub_bins].uri, j);
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

/**
 * Callback function to be called once all inferences (Primary + Secondary)
 * are done. This is opportunity to modify content of the metadata.
 * e.g. Here Person is being replaced with Man/Woman and corresponding counts
 * are being maintained. It should be modified according to network classes
 * or can be removed altogether if not required.
 */
static void
all_bbox_generated (AppCtx * appCtx, GstBuffer * buf,
    NvDsBatchMeta * batch_meta, guint index)
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
            //str_replace (obj->text_params.display_text, "Man", "");
            //str_replace (obj->text_params.display_text, "Person", "Man");
            num_male++;
          } else if (strstr (obj->text_params.display_text, "Woman")) {
            //str_replace (obj->text_params.display_text, "Woman", "");
            //str_replace (obj->text_params.display_text, "Person", "Woman");
            num_female++;
          }
        }
      }
    }
  }
}

/**
 * Function to handle program interrupt signal.
 * It installs default handler after handling the interrupt.
 */
static void
_intr_handler (int signum)
{
  struct sigaction action;

  NVGSTDS_ERR_MSG_V ("User Interrupted.. \n");

  memset (&action, 0, sizeof (action));
  action.sa_handler = SIG_DFL;

  sigaction (SIGINT, &action, NULL);

  cintr = TRUE;
}

/**
 * callback function to print the performance numbers of each stream.
 */
static void
perf_cb (gpointer context, NvDsAppPerfStruct * str)
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
  g_print ("**PERF: ");
  for (i = 0; i < numf; i++) {
    g_print ("%.2f (%.2f)\t", fps[i], fps_avg[i]);
  }
  g_print ("\n");
  g_mutex_unlock (&fps_lock);
}

/**
 * Loop function to check the status of interrupts.
 * It comes out of loop if application got interrupted.
 */
static gboolean
check_for_interrupt (gpointer data)
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

/*
 * Function to install custom handler for program interrupt signal.
 */
static void
_intr_setup (void)
{
  struct sigaction action;

  memset (&action, 0, sizeof (action));
  action.sa_handler = _intr_handler;

  sigaction (SIGINT, &action, NULL);
}

static gboolean
kbhit (void)
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

/*
 * Function to enable / disable the canonical mode of terminal.
 * In non canonical mode input is available immediately (without the user
 * having to type a line-delimiter character).
 */
static void
changemode (int dir)
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

static void
print_runtime_commands (void)
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

/**
 * Loop function to check keyboard inputs and status of each pipeline.
 */
static gboolean
event_thread_func (gpointer arg)
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
  if (!kbhit ()) {
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
      print_runtime_commands ();
      break;
    case 'p':
      for (i = 0; i < num_instances; i++)
        //pause_pipeline (appCtx[i]);
      break;
    case 'r':
      for (i = 0; i < num_instances; i++)
        //resume_pipeline (appCtx[i]);
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

static int
get_source_id_from_coordinates (float x_rel, float y_rel)
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

/**
 * Thread to monitor X window events.
 */
static gpointer
nvds_x_event_thread (gpointer data)
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
                get_source_id_from_coordinates (ev.x * 1.0 / win_attr.width,
                ev.y * 1.0 / win_attr.height);
            if (source_id > -1) {
              g_object_set (G_OBJECT (tiler), "show-source", source_id, NULL);
              source_ids[index] = source_id;
              appCtx[index]->show_bbox_text = TRUE;
            }
          } else if (ev.button == Button3) {
            g_object_set (G_OBJECT (tiler), "show-source", -1, NULL);
            source_ids[index] = -1;
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
            for (i = 0; i < num_instances; i++)
              //pause_pipeline (appCtx[i]);
            break;
          }
          if (e.xkey.keycode == r) {
            for (i = 0; i < num_instances; i++)
              //resume_pipeline (appCtx[i]);
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

/**
 * callback function to add application specific metadata.
 * Here it demonstrates how to display the URI of source in addition to
 * the text generated after inference.
 */
static gboolean
overlay_graphics (AppCtx * appCtx, GstBuffer * buf,
    NvDsBatchMeta * batch_meta, guint index)
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
//  display_meta->text_params[0].font_params.font_size =
//      appCtx->config.osd_config.text_size * 1.5;
//  display_meta->text_params[0].font_params.font_name = "Serif";
//  display_meta->text_params[0].set_bg_clr = 1;
//  display_meta->text_params[0].text_bg_clr = (NvOSD_ColorParams) {
//  0, 0, 0, 1.0};


//  if(nvds_enable_latency_measurement) {
//    g_mutex_lock (&appCtx->latency_lock);
//    latency_info = &appCtx->latency_info[index];
//    display_meta->num_labels++;
//    display_meta->text_params[1].display_text = g_strdup_printf ("Latency: %lf",
//        latency_info->latency);
//    g_mutex_unlock (&appCtx->latency_lock);

//    display_meta->text_params[1].y_offset = (display_meta->text_params[0].y_offset * 2 )+
//      display_meta->text_params[0].font_params.font_size;
//    display_meta->text_params[1].x_offset = 20;
//    display_meta->text_params[1].font_params.font_color = (NvOSD_ColorParams) {
//      0, 1, 0, 1};
//    display_meta->text_params[1].font_params.font_size =
//      appCtx->config.osd_config.text_size * 1.5;
//    display_meta->text_params[1].font_params.font_name = "Arial";
//    display_meta->text_params[1].set_bg_clr = 1;
//    display_meta->text_params[1].text_bg_clr = (NvOSD_ColorParams) {
//      0, 0, 0, 1.0};
//  }

  nvds_add_display_meta_to_frame (nvds_get_nth_frame_meta (batch_meta->
          frame_meta_list, 0), display_meta);
  return TRUE;
}





void MainWindow::load_faces()
{
    qDebug()<<"inside load faces\n";

   // qDebug()<<myStyles::blackFolderRelative<<endl;
   // GetFilesInDirectory(blacklist_g_signa, myStyles::blackFolderRelative.toStdString());
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

     QString cam1 = "/home/sigmind/shyamoli-face.mp4";

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
////   // newFeed2->set_blacklist_descriptor(blacklist_descriptors);
//    feeds.push_back(newFeed2);

//    connect(this, SIGNAL(emitCam2(QString,int)), newFeed2, SLOT(initializeCameraMain(QString,int)));

//    connect(newFeed2, SIGNAL(emitFace(cv::Mat, int)), this, SLOT(addFace_triggered(cv::Mat, int)));
//    connect(newFeed2, SIGNAL(emitLP(QPixmap, int)), this, SLOT(addLPR_triggered(QPixmap, int)));
//    connect(newFeed2, SIGNAL(emitTile(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
//    //connect(newFeed, SIGNAL(emitLP(QPixmap,QString,int)), this, SLOT(addObject(QPixmap,QString,int)));
    //connect(newFeed2, SIGNAL(notify(QPixmap,QString,int)), this, SLOT(makeNotification(QPixmap,QString,int)));




   //   emit emitCam2(cam1,2);

    //flowLayout->addWidget(newFeed2);


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
       this->showMaximized();
//    ui->pauseButton->setHidden(true);
//    ui->playButton->setHidden(true);
//    ui->nextButton->setHidden(true);
 // this->show();
//    thread = new QThread();
//    worker = new Worker();

//    worker->moveToThread(thread);

//    conconnect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
//          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()
    //   connect(worker, SIGNAL(workRequested()), thread, SLOT(start()));

       //  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
       //    connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), worker, SLOT(doWork(QPixmap,QString,int)));
       //   //
//   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
//      connect(worker, SIGNAL(valueChanged(QPixmap,QString,int)), this, SLOT(addLP(QPixmap,QString,int)));
//    connect(worker, SIGNAL(finishedLPR()), thread, SLOT(quit()), Qt::DirectConnection);


     //  struct croppedFace d;

    FRthread = new QThread();

    warker = new Warker();


    warker->moveToThread(FRthread);

     warker->load_template();

   // face_detector = dlib::get_frontal_face_detector();
    qDebug()<<"face detector initiated\n";
   // std::vector<string> names;
          //  GetFilesInDirectory(templates_names,"./faces/temp_late");

     //d.message = "message\n";


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


//    trialTimer= new QTimer(this);
//    connect(trialTimer, SIGNAL(timeout()), this, SLOT(cleanTiles()));
    //trialTimer->start(3600000);


    // Deadly Hack Injection

//    GMainLoop *loop = NULL;
//      GstElement *pipeline = NULL, *streammux = NULL, *sink = NULL, *pgie = NULL,
//          *nvvidconv = NULL, *nvosd = NULL, *tiler = NULL, *dsExample;
//   // #ifdef PLATFORM_TEGRA
//      GstElement *transform = NULL;
//  //  #endif
//      GstBus *bus = NULL;
//      guint bus_watch_id;
//      GstPad *tiler_src_pad = NULL;
//      guint i, num_sources;
//      guint tiler_rows, tiler_columns;
//      guint pgie_batch_size;

   // GMainContext *g_main_context_get_thread_default (void);

    //  gchar videos[4][100] = {"file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4", "file:///home/sigmind/sample_10-normal.mp4"}

//      gchar *videos = (gchar*)g_malloc0(4);
//        videos[0] = "file:///home/sigmind/sample_10-normal.mp4";

//      QString newVid = "file:///home/sigmind/sample_10-normal.mp4";
//      QByteArray ba;
//      ba = newVid.toUtf8();
//      gchar* videos = ba.constData();

//        gboolean fullFrame = FALSE;

//      /* Check input arguments */

//      num_sources = 32;

//      /* Standard GStreamer initialization */
//      gst_init (0, NULL);
//      //loop = g_main_loop_new (NULL, FALSE);

//      /* Create gstreamer elements */
//      /* Create Pipeline element that will form a connection of other elements */
//      pipeline = gst_pipeline_new ("dstest3-pipeline");

//      /* Create nvstreammux instance to form batches from one or more sources. */
//      streammux = gst_element_factory_make ("nvstreammux", "stream-muxer");

//      if (!pipeline || !streammux) {
//        g_printerr ("One element could not be created. Exiting.\n");
//        //// // //return -1;
//      }
//      gst_bin_add (GST_BIN (pipeline), streammux);

//     // gchar* videos[] = {"file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/silicon.mp4","file:///home/sigmind/Videos/trump.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/elon.mp4","file:///home/sigmind/Videos/caprio.mp4","file:///home/sigmind/Videos/zuck.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/silicon.mp4","file:///home/sigmind/Videos/trump.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/elon.mp4","file:///home/sigmind/Videos/caprio.mp4","file:///home/sigmind/Videos/zuck.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/silicon.mp4","file:///home/sigmind/Videos/trump.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/elon.mp4","file:///home/sigmind/Videos/caprio.mp4","file:///home/sigmind/Videos/zuck.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/silicon.mp4","file:///home/sigmind/Videos/trump.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/elon.mp4","file:///home/sigmind/Videos/caprio.mp4","file:///home/sigmind/Videos/zuck.mp4", NULL} ;

//      gchar* videos[] = {"file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4",
//                         "file:///home/sigmind/Videos/trump.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4",
//                         "file:///home/sigmind/Videos/elon.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4",
//                         "file:///home/sigmind/Videos/shyamoli15.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4","file:///home/sigmind/Videos/sample.mp4",
//                         NULL} ;



//      for (i = 0; i < num_sources; i++) {
//        GstPad *sinkpad, *srcpad;
//        gchar pad_name[16] = { };


//        GstElement *source_bin = create_source_bin (i, videos[i]);

//        if (!source_bin) {
//          g_printerr ("Failed to create source bin. Exiting.\n");
//        //  // //return -1;
//        }

//        gst_bin_add (GST_BIN (pipeline), source_bin);



//        srcpad = gst_element_get_static_pad (source_bin, "src");
//        if (!srcpad) {
//          g_printerr ("Failed to get src pad of source bin. Exiting.\n");
//         // // //return -1;
//        }



//        g_snprintf (pad_name, 15, "sink_%u", i);
//        sinkpad = gst_element_get_request_pad (streammux, pad_name);
//        if (!sinkpad) {
//          g_printerr ("Streammux request sink pad failed. Exiting.\n");
//         // // //return -1;
//        }

//        if (gst_pad_link (srcpad, sinkpad) != GST_PAD_LINK_OK) {
//          g_printerr ("Failed to link source bin to stream muxer. Exiting.\n");
//        //  // //return -1;
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
//   //   sink = gst_element_factory_make ("nveglglessink", "nvvideo-renderer");

//      sink = gst_element_factory_make ("nvoverlaysink", "nvvideo-renderer");

//      if (!pgie || !tiler || !nvvidconv || !nvosd || !sink) {
//        g_printerr ("One element could not be created. Exiting.\n");
//      //  // //return -1;
//      }

//    //#ifdef PLATFORM_TEGRA
//      if(!transform) {
//        g_printerr ("One tegra element could not be created. Exiting.\n");
//      //  // //return -1;
//      }
//    //#endif
//  //   g_object_set (G_OBJECT(sink), "sync", FALSE, NULL);
//// overlay-x=0 overlay-y=0 overlay-w=1280 overlay-h=720 overlay=1
//     g_object_set (G_OBJECT (dsExample),
//             "full-frame", fullFrame, NULL);

//     g_object_set(G_OBJECT(sink), "overlay-x", 0, "overlay-y", 15, "overlay-w", 1500, "overlay-h", 1200, "overlay", 1, NULL);

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

//      tiler_rows = (guint) 4;//sqrt (num_sources);
//      tiler_columns = (guint) 8;//ceil (1.0 * num_sources / tiler_rows);
//      /* we set the tiler properties here */
//      g_object_set (G_OBJECT (tiler), "rows", tiler_rows, "columns", tiler_columns,
//          "width", TILED_OUTPUT_WIDTH, "height", TILED_OUTPUT_HEIGHT, NULL);

//      /* we add a message handler */
////      bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
////      bus_watch_id = gst_bus_add_watch (bus, bus_call, NULL);
////      gst_object_unref (bus);

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
//      //  // //return -1;
//      }
////    #else
////    gst_bin_add_many (GST_BIN (pipeline), pgie, tiler, nvvidconv, nvosd, sink,
////          NULL);
////      /* we link the elements together
////       * nvstreammux -> nvinfer -> nvtiler -> nvvidconv -> nvosd -> video-renderer */
////      if (!gst_element_link_many (streammux, pgie, tiler, nvvidconv, nvosd, sink,
////              NULL)) {
////        g_printerr ("Elements could not be linked. Exiting.\n");
////        // //return -1;
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

//    // g_signal_connect(G_OBJECT(tiler_src_pad), "src", G_CALLBACK(tiler_src_pad_buffer_probe), &d);


//      /* Set the pipeline to "playing" state */
////      g_print ("Now playing:");
////      for (i = 0; i < num_sources; i++) {
////        g_print (" %s,", argv[i + 1]);
////      }
//      g_print ("\n");
//      gst_element_set_state (pipeline, GST_STATE_PLAYING);

//      /* Wait till pipeline encounters an error or EOS */
//      g_print ("Running...\n");
////   //   g_main_loop_run (loop);
////      while(1) {
//// //g_main_iteration(false);
//// g_main_context_iteration(NULL, TRUE);
//GMainContext *context = g_main_context_default ();
// gboolean quit = FALSE;
//g_main_context_push_thread_default (context);
// /* Set up the D-Bus connection to work in the GLib event loop. */
// //dbus_connection_setup_with_g_main (dbus_connection, context);

// /* Run the GLib event loop. */
// while (1) {

//     if(!loop_off) {
//   g_main_context_iteration (context, FALSE);


//      if (frameQueue.size() > 0) {
//                      qDebug() << " Frame size CV  ............ shuvom";
////                   //  g_main_iteration(false);
////                       g_main_context_iteration (context, FALSE);
//                    cv::Mat frameSinK = frameQueue.front();

//////                    cv::Size sz = frameSinK.size();
//////                    int imageWidth = sz.width;
//////                    int imageHeight = sz.height;
//////                    qDebug() << " Image Width = " << QString::number(imageWidth) <<  " Heighht = " << QString::number(imageHeight);
////                  //  if(imageWidth > 0 && imageHeight > 0){
//////                    int rows = frameSinK.rows;
//////                     int cols = frameSinK.cols;
//////                      std::cout<< " FrameSinK = " << rows<<" "<<cols<<std::endl;
//                    if( frameSinK.empty())                      // Check for invalid input
//                       {
//                              std::cout <<  "Could not open or find the image" << std::endl ;

//                            }
//                    else {
//                // g_main_context_iteration(NULL, FALSE);
//                        qDebug() << " Before Emit .....";
//                        emit emitDSFace(frameSinK.clone(), 5);

//                     //
//                    //    g_object_set(G_OBJECT(sink), "overlay-x", 0, "overlay-y", 100, "overlay-w", 500, "overlay-h", 800, "overlay", 1, NULL);



//                       // frameSinK.release();
//                        qDebug() << " Frame Queue Cleared";

//                    }


//                     frameQueue.clear();
//                    frameSinK.release();





//     }

//     }



//     }




 ////////////////////////////////////////////////////////////////////////////////////////// END of EX3 ->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
 ///
 ///


    printf(" starting");
  GOptionContext *ctx = NULL;
  GOptionGroup *group = NULL;
  GError *error = NULL;
  guint i;
printf(" defining arguments");
  gint myargc=3;
  char *array[] = {
       "./deepstream-appQT",
       "-c",
       "/home/sigmind/deepstream_sdk_v4.0_jetson/sources/apps/sample_apps/deepstream-app/source30_1080p_dec_infer-resnet_tiled_display_int8.txt",
       NULL
  };

//  gchar vp = 'file:///home/sigmind/sample_720p.h264';
 // char *my = &yy;
//  gchar **n = &m;
//  gchar ***myargv = &n;

  //char* ptr = array;
  char** myargv = array;


  ctx = g_option_context_new ("Nvidia DeepStream Demo");
  group = g_option_group_new ("abc", NULL, NULL, NULL, NULL);
  g_option_group_add_entries (group, entries);

  g_option_context_set_main_group (ctx, group);
  g_option_context_add_group (ctx, gst_init_get_option_group ());

  GST_DEBUG_CATEGORY_INIT (NVDS_APP, "NVDS_APP", 0, NULL);

  if (!g_option_context_parse (ctx, &myargc, &myargv, &error)) {
    NVGSTDS_ERR_MSG_V ("%s", error->message);
   // //return -1;
  }

  if (print_version) {
    g_print ("deepstream-app version %d.%d\n",
        NVDS_APP_VERSION_MAJOR, NVDS_APP_VERSION_MINOR);
    nvds_version_print ();
   // //return 0;
  }

  if (print_dependencies_version) {
    g_print ("deepstream-app version %d.%d\n",
        NVDS_APP_VERSION_MAJOR, NVDS_APP_VERSION_MINOR);
    nvds_version_print ();
    nvds_dependencies_version_print ();
    //return 0;
  }



  if (cfg_files) {
    num_instances = g_strv_length (cfg_files);
  }
  if (input_files) {
    num_input_files = g_strv_length (input_files);
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

 //NVGSTDS_ERR_MSG_V ("Failed to parse config file ");
    if (!parse_config_file (&appCtx[i]->config, cfg_files[i])) {
      NVGSTDS_ERR_MSG_V ("Failed to parse config file '%s'", cfg_files[i]);
      appCtx[i]->return_value = -1;
      goto done;
    }
  }

  for (i = 0; i < num_instances; i++) {
    if (!create_pipeline (appCtx[i], NULL,
            all_bbox_generated, perf_cb, overlay_graphics)) {
      NVGSTDS_ERR_MSG_V ("Failed to create pipeline");
      return_value = -1;
      goto done;
    }
  }

  main_loop = g_main_loop_new (NULL, FALSE);

  _intr_setup ();
  g_timeout_add (400, check_for_interrupt, NULL);


  g_mutex_init (&disp_lock);
  display = XOpenDisplay (NULL);
  for (i = 0; i < num_instances; i++) {
    guint j;

    if (gst_element_set_state (appCtx[i]->pipeline.pipeline,
            GST_STATE_PAUSED) == GST_STATE_CHANGE_FAILURE) {
      NVGSTDS_ERR_MSG_V ("Failed to set pipeline to PAUSED");
      return_value = -1;
      goto done;
    }

    if (!appCtx[i]->config.tiled_display_config.enable)
      continue;

    for (j = 0; j < appCtx[i]->config.num_sink_sub_bins; j++) {
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
        goto done;
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

      windows[i] =
          XCreateSimpleWindow (display, RootWindow (display,
              DefaultScreen (display)), 0, 0, width, height, 2, 0x00000000,
          0x00000000);

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
      XMapRaised (display, windows[i]);
      XSync (display, 1);       //discard the events for now
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
        goto done;
      }
    }
  }

  print_runtime_commands ();

  changemode (1);

  g_timeout_add (40, event_thread_func, NULL);
  g_main_loop_run (main_loop);

  changemode (0);

done:

  g_print ("Quitting\n");
  for (i = 0; i < num_instances; i++) {
    if (appCtx[i]->return_value == -1)
      return_value = -1;
    //destroy_pipeline (appCtx[i]);

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




 /* To exit the main loop (from a callback implementing your D-Bus Quit() function): */
// quit = TRUE;
// g_main_context_wakeup (NULL  /* global default main context */);

      /* Out of the main loop, clean up nicely */

//      g_print ("Returned, stopping playback\n");
//      gst_element_set_state (pipeline, GST_STATE_NULL);
//      g_print ("Deleting pipeline\n");
//      gst_object_unref (GST_OBJECT (pipeline));
//      g_source_remove (bus_watch_id);
//      g_main_loop_unref (loop);

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

    //warker->abort();
    FRthread->wait();
    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
    delete FRthread;
    //delete warker;
   // delete newFeed2;
   // delete newFeed3;
    //delete newFeed4;

//    g_print ("Returned, stopping playback\n");
//    gst_element_set_state (pipeline, GST_STATE_NULL);
//    g_print ("Deleting pipeline\n");
//    gst_object_unref (GST_OBJECT (pipeline));
//    g_source_remove (bus_watch_id);
//    g_main_loop_unref (loop);

    delete ui;
}

void MainWindow::emitFunction(cv::Mat foo)
{
    emit emitDSFace(foo.clone(), 5);

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
    nots->setFixedHeight(1000);
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


//    FRthread = new QThread();
//    warker = new Warker();

//    warker->moveToThread(FRthread);
//   // warker->setup(templates_names, template_descriptors);
//  //  connect(this,SIGNAL(load_template()), warker, SLOT(receive_template()));

//   //  load_faces();
//    connect(warker, SIGNAL(warkRequested()), FRthread, SLOT(start()));

//  //  connect(thread, SIGNAL(started()), worker, SLOT(doWork(int)));
//    connect(this, SIGNAL(requestUpdateFR(cv::Mat,QString,int)), warker, SLOT(doWark(cv::Mat,QString,int)));
//   //connect(this, SIGNAL(requestUpdateLPR(QPixmap,QString,int)), this, SLOT(valueChanged(QPixmap,QString,int));
//          //  connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT()

//   // connect(worker,SIGNAL(valueChangedLPR(QString)), this, SLOT(valueChanged(QPixmap,QString,int)));
//      connect(warker, SIGNAL(valueFRChanged(QPixmap,QString,int,matrix<float,0,1>)), this, SLOT(addFR(QPixmap,QString,int,matrix<float,0,1>)));
//    connect(warker, SIGNAL(finishedFR()), FRthread, SLOT(quit()), Qt::DirectConnection);


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

    qDebug() << " Inside addFace_triggered";
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
     //   facesWindow->addFaceRecognized(pic, str, indx);// }

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
    //loop_off = TRUE;

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
//trialTimer->stop();
//    if (facesWindow != nullptr)
//       {
//        facesWindow->deleteLater();
//          // delete facesWindow;
//        facesWindow = new Faces(this);
//         trialTimer->start(3600000);
//        // facesWindow->setAttribute( Qt::WA_DeleteOnClose , true);
//       }
}
