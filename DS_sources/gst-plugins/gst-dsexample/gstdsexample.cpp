/**
 * Copyright (c) 2017-2020, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <ostream>
#include <fstream>
#include "gstdsexample.h"
#include <sys/time.h>
// #include<bits/stdc++.h>
using namespace std;
GST_DEBUG_CATEGORY_STATIC(gst_dsexample_debug);
#define GST_CAT_DEFAULT gst_dsexample_debug
#define USE_EGLIMAGE 1
/* enable to write transformed cvmat to files */
#define DSEXAMPLE_DEBUG
static GQuark _dsmeta_quark = 0;

// #define NVDS_USER_FRAME_META_EXAMPLE (nvds_get_user_meta_type((gchar *)"NVIDIA.NVINFER.USER_META"))
#define NVDS_USER_FRAME_META_EXAMPLE (nvds_get_user_meta_type((gchar *)"NVIDIA.NVDSEXAMPLE.EXAMPLE_META"))

/* Enum to identify properties */
enum
{
    PROP_0,
    PROP_UNIQUE_ID,
    PROP_PROCESSING_WIDTH,
    PROP_PROCESSING_HEIGHT,
    PROP_PROCESS_FULL_FRAME,
    PROP_BLUR_OBJECTS,
    PROP_GPU_DEVICE_ID
};

#define CHECK_NVDS_MEMORY_AND_GPUID(object, surface)                                                   \
    ({                                                                                                   \
    int _errtype = 0;                                                                                  \
    do                                                                                                 \
{                                                                                                  \
    if ((surface->memType == NVBUF_MEM_DEFAULT || surface->memType == NVBUF_MEM_CUDA_DEVICE) &&      \
    (surface->gpuId != object->gpu_id))                                                          \
{                                                                                                \
    GST_ELEMENT_ERROR(object, RESOURCE, FAILED,                                                    \
    ("Input surface gpu-id doesnt match with configured gpu-id for element,"     \
    " please allocate input using unified memory, or use same gpu-ids"),        \
    ("surface-gpu-id=%d,%s-gpu-id=%d", surface->gpuId, GST_ELEMENT_NAME(object), \
    object->gpu_id));                                                           \
    _errtype = 1;                                                                                  \
    }                                                                                                \
    } while (0);                                                                                       \
    _errtype;                                                                                          \
    })

/* Default values for properties */
#define DEFAULT_UNIQUE_ID 15
#define DEFAULT_PROCESSING_WIDTH 640
#define DEFAULT_PROCESSING_HEIGHT 480
#define DEFAULT_PROCESS_FULL_FRAME TRUE
#define DEFAULT_BLUR_OBJECTS FALSE
#define DEFAULT_GPU_ID 0

#define RGB_BYTES_PER_PIXEL 3
#define RGBA_BYTES_PER_PIXEL 4
#define Y_BYTES_PER_PIXEL 1
#define UV_BYTES_PER_PIXEL 2

#define MIN_INPUT_OBJECT_WIDTH 16
#define MIN_INPUT_OBJECT_HEIGHT 16

#define CHECK_NPP_STATUS(npp_status, error_str)             \
    do                                                        \
{                                                         \
    if ((npp_status) != NPP_SUCCESS)                        \
{                                                       \
    g_print("Error: %s in %s at line %d: NPP Error %d\n", \
    error_str, __FILE__, __LINE__, npp_status);   \
    goto error;                                           \
    }                                                       \
    } while (0)

#define CHECK_CUDA_STATUS(cuda_status, error_str)                            \
    do                                                                         \
{                                                                          \
    if ((cuda_status) != cudaSuccess)                                        \
{                                                                        \
    g_print("Error: %s in %s at line %d (%s)\n",                           \
    error_str, __FILE__, __LINE__, cudaGetErrorName(cuda_status)); \
    goto error;                                                            \
    }                                                                        \
    } while (0)

/* By default NVIDIA Hardware allocated memory flows through the pipeline. We
 * will be processing on this type of memory only. */
#define GST_CAPS_FEATURE_MEMORY_NVMM "memory:NVMM"
static GstStaticPadTemplate gst_dsexample_sink_template =
        GST_STATIC_PAD_TEMPLATE("sink",
                                GST_PAD_SINK,
                                GST_PAD_ALWAYS,
                                GST_STATIC_CAPS(GST_VIDEO_CAPS_MAKE_WITH_FEATURES(GST_CAPS_FEATURE_MEMORY_NVMM,
                                                                                  "{ NV12, RGBA, I420 }")));

static GstStaticPadTemplate gst_dsexample_src_template =
        GST_STATIC_PAD_TEMPLATE("src",
                                GST_PAD_SRC,
                                GST_PAD_ALWAYS,
                                GST_STATIC_CAPS(GST_VIDEO_CAPS_MAKE_WITH_FEATURES(GST_CAPS_FEATURE_MEMORY_NVMM,
                                                                                  "{ NV12, RGBA, I420 }")));

/* Define our element type. Standard GObject/GStreamer boilerplate stuff */
#define gst_dsexample_parent_class parent_class
G_DEFINE_TYPE(GstDsExample, gst_dsexample, GST_TYPE_BASE_TRANSFORM);

static void gst_dsexample_set_property(GObject *object, guint prop_id,
                                       const GValue *value, GParamSpec *pspec);
static void gst_dsexample_get_property(GObject *object, guint prop_id,
                                       GValue *value, GParamSpec *pspec);

static gboolean gst_dsexample_set_caps(GstBaseTransform *btrans,
                                       GstCaps *incaps, GstCaps *outcaps);
static gboolean gst_dsexample_start(GstBaseTransform *btrans);
static gboolean gst_dsexample_stop(GstBaseTransform *btrans);

static GstFlowReturn gst_dsexample_transform_ip(GstBaseTransform *
                                                btrans,
                                                GstBuffer *inbuf);

static void
attach_metadata_full_frame(GstDsExample *dsexample, NvDsFrameMeta *frame_meta,
                           gdouble scale_ratio, DsExampleOutput *output, guint batch_id);
static void attach_metadata_object(GstDsExample *dsexample,
                                   NvDsObjectMeta *obj_meta, DsExampleOutput *output);

void *set_metadata_ptr(cv::Mat fram);

void *set_metadata_ptr(cv::Mat fram)
{
    // gchar *user_metadata = (gchar*)g_malloc0(USER_ARRAY_SIZE);
    cv::Mat *user_metadata = (cv::Mat*)g_malloc0(1000);
    fram.copyTo(*user_metadata);

    return (void *)user_metadata;
}

/* Install properties, set sink and src pad capabilities, override the required
 * functions of the base class, These are common to all instances of the
 * element.
 */
static void
gst_dsexample_class_init(GstDsExampleClass *klass)
{
    printf("\ntester-1 gst_dsexample_class_init\n");

    GObjectClass *gobject_class;
    GstElementClass *gstelement_class;
    GstBaseTransformClass *gstbasetransform_class;

    /* Indicates we want to use DS buf api */
    g_setenv("DS_NEW_BUFAPI", "1", TRUE);

    gobject_class = (GObjectClass *)klass;
    gstelement_class = (GstElementClass *)klass;
    gstbasetransform_class = (GstBaseTransformClass *)klass;

    /* Overide base class functions */
    gobject_class->set_property = GST_DEBUG_FUNCPTR(gst_dsexample_set_property);
    gobject_class->get_property = GST_DEBUG_FUNCPTR(gst_dsexample_get_property);

    gstbasetransform_class->set_caps = GST_DEBUG_FUNCPTR(gst_dsexample_set_caps);
    gstbasetransform_class->start = GST_DEBUG_FUNCPTR(gst_dsexample_start);
    gstbasetransform_class->stop = GST_DEBUG_FUNCPTR(gst_dsexample_stop);

    gstbasetransform_class->transform_ip =
            GST_DEBUG_FUNCPTR(gst_dsexample_transform_ip);

    /* Install properties */
    g_object_class_install_property(gobject_class, PROP_UNIQUE_ID,
                                    g_param_spec_uint("unique-id",
                                                      "Unique ID",
                                                      "Unique ID for the element. Can be used to identify output of the"
                                                      " element",
                                                      0, G_MAXUINT, DEFAULT_UNIQUE_ID, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

    g_object_class_install_property(gobject_class, PROP_PROCESSING_WIDTH,
                                    g_param_spec_int("processing-width",
                                                     "Processing Width",
                                                     "Width of the input buffer to algorithm",
                                                     1, G_MAXINT, DEFAULT_PROCESSING_WIDTH, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

    g_object_class_install_property(gobject_class, PROP_PROCESSING_HEIGHT,
                                    g_param_spec_int("processing-height",
                                                     "Processing Height",
                                                     "Height of the input buffer to algorithm",
                                                     1, G_MAXINT, DEFAULT_PROCESSING_HEIGHT, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

    g_object_class_install_property(gobject_class, PROP_PROCESS_FULL_FRAME,
                                    g_param_spec_boolean("full-frame",
                                                         "Full frame",
                                                         "Enable to process full frame or disable to process objects detected"
                                                         "by primary detector",
                                                         DEFAULT_PROCESS_FULL_FRAME, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

    g_object_class_install_property(gobject_class, PROP_BLUR_OBJECTS,
                                    g_param_spec_boolean("blur-objects",
                                                         "Blur Objects",
                                                         "Enable to blur the objects detected in full-frame=0 mode"
                                                         "by primary detector",
                                                         DEFAULT_BLUR_OBJECTS, (GParamFlags)(G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS)));

    g_object_class_install_property(gobject_class, PROP_GPU_DEVICE_ID,
                                    g_param_spec_uint("gpu-id",
                                                      "Set GPU Device ID",
                                                      "Set GPU Device ID", 0,
                                                      G_MAXUINT, 0,
                                                      GParamFlags(G_PARAM_READWRITE |
                                                                  G_PARAM_STATIC_STRINGS | GST_PARAM_MUTABLE_READY)));
    /* Set sink and src pad capabilities */
    gst_element_class_add_pad_template(gstelement_class,
                                       gst_static_pad_template_get(&gst_dsexample_src_template));
    gst_element_class_add_pad_template(gstelement_class,
                                       gst_static_pad_template_get(&gst_dsexample_sink_template));

    /* Set metadata describing the element */
    gst_element_class_set_details_simple(gstelement_class,
                                         "DsExample plugin",
                                         "DsExample Plugin",
                                         "Process a 3rdparty example algorithm on objects / full frame",
                                         "NVIDIA Corporation. Post on Deepstream for Tesla forum for any queries "
                                         "@ https://devtalk.nvidia.com/default/board/209/");
}

static void
gst_dsexample_init(GstDsExample *dsexample)
{
    printf("\ntester-2 gst_dsexample_init\n");

    GstBaseTransform *btrans = GST_BASE_TRANSFORM(dsexample);

    /* We will not be generating a new buffer. Just adding / updating
   * metadata. */
    gst_base_transform_set_in_place(GST_BASE_TRANSFORM(btrans), TRUE);
    /* We do not want to change the input caps. Set to passthrough. transform_ip
   * is still called. */
    gst_base_transform_set_passthrough(GST_BASE_TRANSFORM(btrans), TRUE);

    /* Initialize all property variables to default values */
    dsexample->unique_id = DEFAULT_UNIQUE_ID;
    dsexample->processing_width = DEFAULT_PROCESSING_WIDTH;
    dsexample->processing_height = DEFAULT_PROCESSING_HEIGHT;
    dsexample->process_full_frame = DEFAULT_PROCESS_FULL_FRAME;
    dsexample->blur_objects = DEFAULT_BLUR_OBJECTS;
    dsexample->gpu_id = DEFAULT_GPU_ID;
    /* This quark is required to identify NvDsMeta when iterating through
   * the buffer metadatas */
    if (!_dsmeta_quark)
        _dsmeta_quark = g_quark_from_static_string(NVDS_META_STRING);
}

/* Function called when a property of the element is set. Standard boilerplate.
 */
static void
gst_dsexample_set_property(GObject *object, guint prop_id,
                           const GValue *value, GParamSpec *pspec)
{
    printf("\ntester-3 gst_dsexample_set_property\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(object);
    switch (prop_id)
    {
    case PROP_UNIQUE_ID:
        dsexample->unique_id = g_value_get_uint(value);
        break;
    case PROP_PROCESSING_WIDTH:
        dsexample->processing_width = g_value_get_int(value);
        break;
    case PROP_PROCESSING_HEIGHT:
        dsexample->processing_height = g_value_get_int(value);
        break;
    case PROP_PROCESS_FULL_FRAME:
        dsexample->process_full_frame = g_value_get_boolean(value);
        break;
    case PROP_BLUR_OBJECTS:
        dsexample->blur_objects = g_value_get_boolean(value);
        break;
    case PROP_GPU_DEVICE_ID:
        dsexample->gpu_id = g_value_get_uint(value);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

/* Function called when a property of the element is requested. Standard
 * boilerplate.
 */
static void
gst_dsexample_get_property(GObject *object, guint prop_id,
                           GValue *value, GParamSpec *pspec)
{
    printf("\ntester-4 gst_dsexample_get_property\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(object);

    switch (prop_id)
    {
    case PROP_UNIQUE_ID:
        g_value_set_uint(value, dsexample->unique_id);
        break;
    case PROP_PROCESSING_WIDTH:
        g_value_set_int(value, dsexample->processing_width);
        break;
    case PROP_PROCESSING_HEIGHT:
        g_value_set_int(value, dsexample->processing_height);
        break;
    case PROP_PROCESS_FULL_FRAME:
        g_value_set_boolean(value, dsexample->process_full_frame);
        break;
    case PROP_BLUR_OBJECTS:
        g_value_set_boolean(value, dsexample->blur_objects);
        break;
    case PROP_GPU_DEVICE_ID:
        g_value_set_uint(value, dsexample->gpu_id);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}

/**
 * Initialize all resources and start the output thread
 */
static gboolean
gst_dsexample_start(GstBaseTransform *btrans)
{
    printf("\ntester-5 gst_dsexample_start\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(btrans);
    NvBufSurfaceCreateParams create_params;
    DsExampleInitParams init_params =
    {dsexample->processing_width, dsexample->processing_height,
     dsexample->process_full_frame};

    GstQuery *queryparams = NULL;
    guint batch_size = 1;

    /* Algorithm specific initializations and resource allocation. */
    dsexample->dsexamplelib_ctx = DsExampleCtxInit(&init_params);

    GST_DEBUG_OBJECT(dsexample, "ctx lib %p \n", dsexample->dsexamplelib_ctx);

    CHECK_CUDA_STATUS(cudaSetDevice(dsexample->gpu_id),
                      "Unable to set cuda device");

    dsexample->batch_size = 1;
    queryparams = gst_nvquery_batch_size_new();
    if (gst_pad_peer_query(GST_BASE_TRANSFORM_SINK_PAD(btrans), queryparams) || gst_pad_peer_query(GST_BASE_TRANSFORM_SRC_PAD(btrans), queryparams))
    {
        if (gst_nvquery_batch_size_parse(queryparams, &batch_size))
        {
            dsexample->batch_size = batch_size;
        }
    }
    GST_DEBUG_OBJECT(dsexample, "Setting batch-size %d \n",
                     dsexample->batch_size);
    gst_query_unref(queryparams);

    if (dsexample->process_full_frame && dsexample->blur_objects)
    {
        GST_ERROR("Error: does not support blurring while processing full frame");
        goto error;
    }

    CHECK_CUDA_STATUS(cudaStreamCreate(&dsexample->cuda_stream),
                      "Could not create cuda stream");

    if (dsexample->inter_buf)
        NvBufSurfaceDestroy(dsexample->inter_buf);
    dsexample->inter_buf = NULL;

    /* An intermediate buffer for NV12/RGBA to BGR conversion  will be
   * required. Can be skipped if custom algorithm can work directly on NV12/RGBA. */
    create_params.gpuId = dsexample->gpu_id;
    create_params.width = dsexample->processing_width;
    create_params.height = dsexample->processing_height;
    create_params.size = 0;
    create_params.colorFormat = NVBUF_COLOR_FORMAT_RGBA;
    create_params.layout = NVBUF_LAYOUT_PITCH;
#ifdef __aarch64__
    create_params.memType = NVBUF_MEM_DEFAULT;
#else
    create_params.memType = NVBUF_MEM_CUDA_UNIFIED;
#endif

    if (NvBufSurfaceCreate(&dsexample->inter_buf, 1,
                           &create_params) != 0)
    {
        GST_ERROR("Error: Could not allocate internal buffer for dsexample");
        goto error;
    }

    /* Create host memory for storing converted/scaled interleaved RGB data */
    CHECK_CUDA_STATUS(cudaMallocHost(&dsexample->host_rgb_buf,
                                     dsexample->processing_width * dsexample->processing_height *
                                     RGB_BYTES_PER_PIXEL),
                      "Could not allocate cuda host buffer");

    GST_DEBUG_OBJECT(dsexample, "allocated cuda buffer %p \n",
                     dsexample->host_rgb_buf);

    /* CV Mat containing interleaved RGB data. This call does not allocate memory.
   * It uses host_rgb_buf as data. */
    dsexample->cvmat =
            new cv::Mat(dsexample->processing_height, dsexample->processing_width,
                        CV_8UC3, dsexample->host_rgb_buf,
                        dsexample->processing_width * RGB_BYTES_PER_PIXEL);

    if (!dsexample->cvmat){
        printf("\ncvmat is null, goto error!\n");
        goto error;
    }

    GST_DEBUG_OBJECT(dsexample, "created CV Mat\n");

    return TRUE;
error:
    if (dsexample->host_rgb_buf)
    {
        cudaFreeHost(dsexample->host_rgb_buf);
        dsexample->host_rgb_buf = NULL;
    }

    if (dsexample->cuda_stream)
    {
        cudaStreamDestroy(dsexample->cuda_stream);
        dsexample->cuda_stream = NULL;
    }
    if (dsexample->dsexamplelib_ctx){
        printf("\ngoto dsexampleCtxDeinit function\n");
        DsExampleCtxDeinit(dsexample->dsexamplelib_ctx);
    }
        return FALSE;
}

/**
 * Stop the output thread and free up all the resources
 */
static gboolean
gst_dsexample_stop(GstBaseTransform *btrans)
{
    printf("\ntester-6 gst_dsexample_stop\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(btrans);

    if (dsexample->inter_buf)
        NvBufSurfaceDestroy(dsexample->inter_buf);
    dsexample->inter_buf = NULL;

    if (dsexample->cuda_stream)
        cudaStreamDestroy(dsexample->cuda_stream);
    dsexample->cuda_stream = NULL;

    delete dsexample->cvmat;
    dsexample->cvmat = NULL;

    if (dsexample->host_rgb_buf)
    {
        cudaFreeHost(dsexample->host_rgb_buf);
        dsexample->host_rgb_buf = NULL;
    }

    GST_DEBUG_OBJECT(dsexample, "deleted CV Mat \n");

    /* Deinit the algorithm library */
    DsExampleCtxDeinit(dsexample->dsexamplelib_ctx);
    dsexample->dsexamplelib_ctx = NULL;

    GST_DEBUG_OBJECT(dsexample, "ctx lib released \n");

    return TRUE;
}

/**
 * Called when source / sink pad capabilities have been negotiated.
 */
static gboolean
gst_dsexample_set_caps(GstBaseTransform *btrans, GstCaps *incaps,
                       GstCaps *outcaps)
{
    printf("\ntester-7 gst_dsexample_set_caps\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(btrans);
    /* Save the input video information, since this will be required later. */
    gst_video_info_from_caps(&dsexample->video_info, incaps);

    if (dsexample->blur_objects && !dsexample->process_full_frame)
    {
        /* requires RGBA format for blurring the objects in opencv */
        if (dsexample->video_info.finfo->format != GST_VIDEO_FORMAT_RGBA)
        {
            GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                              ("input format should be RGBA when using blur-objects property"), (NULL));
            goto error;
        }
    }

    return TRUE;

error:
    return FALSE;
}

/**
 * Scale the entire frame to the processing resolution maintaining aspect ratio.
 * Or crop and scale objects to the processing resolution maintaining the aspect
 * ratio. Remove the padding required by hardware and convert from RGBA to RGB
 * using openCV. These steps can be skipped if the algorithm can work with
 * padded data and/or can work with RGBA.
 */
static GstFlowReturn
get_converted_mat(GstDsExample *dsexample, NvBufSurface *input_buf, gint idx,
                  NvOSD_RectParams *crop_rect_params, gdouble &ratio, gint input_width,
                  gint input_height)
{
    printf("\n tester_again-3 get_converted_mat come from gst_dsexample_transform_ip method\n");

    NvBufSurfTransform_Error err;
    NvBufSurfTransformConfigParams transform_config_params;
    NvBufSurfTransformParams transform_params;
    NvBufSurfTransformRect src_rect;
    NvBufSurfTransformRect dst_rect;
    NvBufSurface ip_surf;
    cv::Mat in_mat;
    ip_surf = *input_buf;

    ip_surf.numFilled = ip_surf.batchSize = 1;
    ip_surf.surfaceList = &(input_buf->surfaceList[idx]);

    g_print("left : %f top: %f width: %f height: %f",crop_rect_params->left,crop_rect_params->top,crop_rect_params->width,crop_rect_params->height);

    float x = crop_rect_params->left- 10;
    float y = crop_rect_params->top - 10.0 ;
    float w = crop_rect_params->width + 20;
    float h = crop_rect_params->height + 20.0;

    gint src_left = GST_ROUND_UP_2((unsigned int)x);
    gint src_top = GST_ROUND_UP_2((unsigned int)y);
    gint src_width = GST_ROUND_DOWN_2((unsigned int)w);
    gint src_height = GST_ROUND_DOWN_2((unsigned int)h);

    /* Maintain aspect ratio */
    double hdest = dsexample->processing_width * src_height / (double)src_width;
    double wdest = dsexample->processing_height * src_width / (double)src_height;
    guint dest_width, dest_height;

    if (hdest <= dsexample->processing_height)
    {
        dest_width = dsexample->processing_width;
        dest_height = hdest;
    }
    else
    {
        dest_width = wdest;
        dest_height = dsexample->processing_height;
    }

    /* Configure transform session parameters for the transformation */
    transform_config_params.compute_mode = NvBufSurfTransformCompute_Default;
    transform_config_params.gpu_id = dsexample->gpu_id;
    transform_config_params.cuda_stream = dsexample->cuda_stream;

    /* Set the transform session parameters for the conversions executed in this
   * thread. */
    err = NvBufSurfTransformSetSessionParams(&transform_config_params);
    if (err != NvBufSurfTransformError_Success)
    {
        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                          ("NvBufSurfTransformSetSessionParams failed with error %d", err), (NULL));
        goto error;
    }

    /* Calculate scaling ratio while maintaining aspect ratio */
    ratio = MIN(1.0 * dest_width / src_width, 1.0 * dest_height / src_height);

    if ((crop_rect_params->width == 0) || (crop_rect_params->height == 0))
    {
        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                          ("%s:crop_rect_params dimensions are zero", __func__), (NULL));
        goto error;
    }

#ifdef __aarch64__
    if (ratio <= 1.0 / 16 || ratio >= 16.0)
    {
        /* Currently cannot scale by ratio > 16 or < 1/16 for Jetson */
        goto error;
    }
#endif
    /* Set the transform ROIs for source and destination */
    src_rect = {(guint)src_top, (guint)src_left, (guint)src_width, (guint)src_height};
    dst_rect = {0, 0, (guint)dest_width, (guint)dest_height};

    /* Set the transform parameters */
    transform_params.src_rect = &src_rect;
    transform_params.dst_rect = &dst_rect;
    transform_params.transform_flag =
            NVBUFSURF_TRANSFORM_FILTER | NVBUFSURF_TRANSFORM_CROP_SRC |
            NVBUFSURF_TRANSFORM_CROP_DST;
    transform_params.transform_filter = NvBufSurfTransformInter_Default;

    /* Memset the memory */
    NvBufSurfaceMemSet(dsexample->inter_buf, 0, 0, 0);

    GST_DEBUG_OBJECT(dsexample, "Scaling and converting input buffer\n");

    /* Transformation scaling+format conversion if any. */
    err = NvBufSurfTransform(&ip_surf, dsexample->inter_buf, &transform_params);
    if (err != NvBufSurfTransformError_Success)
    {
        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                          ("NvBufSurfTransform failed with error %d while converting buffer", err),
                          (NULL));
        goto error;
    }
    /* Map the buffer so that it can be accessed by CPU */
    if (NvBufSurfaceMap(dsexample->inter_buf, 0, 0, NVBUF_MAP_READ) != 0)
    {
        goto error;
    }

    /* Cache the mapped data for CPU access */
    NvBufSurfaceSyncForCpu(dsexample->inter_buf, 0, 0);

    /* Use openCV to remove padding and convert RGBA to BGR. Can be skipped if
   * algorithm can handle padded RGBA data. */
    in_mat =
            cv::Mat(dsexample->processing_height, dsexample->processing_width,
                    CV_8UC4, dsexample->inter_buf->surfaceList[0].mappedAddr.addr[0],
            dsexample->inter_buf->surfaceList[0].pitch);

#if (CV_MAJOR_VERSION >= 4)
    cv::cvtColor(in_mat, *dsexample->cvmat, cv::COLOR_RGBA2BGR);
#else
    cv::cvtColor(in_mat, *dsexample->cvmat, CV_RGBA2BGR);
#endif

//	   static guint cnt = 0;
//            cv::imwrite("/home/sigmind/Pictures/dsexample/cnts_" + std::to_string (cnt) + ".jpeg", *dsexample->cvmat);
//             cnt++;

    if (NvBufSurfaceUnMap(dsexample->inter_buf, 0, 0))
    {
        goto error;
    }

#ifdef __aarch64__
    /* To use the converted buffer in CUDA, create an EGLImage and then use
   * CUDA-EGL interop APIs */
    if (USE_EGLIMAGE)
    {
        if (NvBufSurfaceMapEglImage(dsexample->inter_buf, 0) != 0)
        {
            goto error;
        }

        /* dsexample->inter_buf->surfaceList[0].mappedAddr.eglImage
     * Use interop APIs cuGraphicsEGLRegisterImage and
     * cuGraphicsResourceGetMappedEglFrame to access the buffer in CUDA */

        /* Destroy the EGLImage */
        NvBufSurfaceUnMapEglImage(dsexample->inter_buf, 0);
    }
#endif

    /* We will first convert only the Region of Interest (the entire frame or the
   * object bounding box) to RGB and then scale the converted RGB frame to
   * processing resolution. */
    return GST_FLOW_OK;

error:
    return GST_FLOW_ERROR;
}

/*
 * Blur the detected objects when processing in object mode (full-frame=0)
 */
static GstFlowReturn
blur_objects(GstDsExample *dsexample, gint idx,
             NvOSD_RectParams *crop_rect_params, cv::Mat in_mat)
{
    printf("\n tester-9 blur_objects\n");

    cv::Rect crop_rect;

    if ((crop_rect_params->width == 0) || (crop_rect_params->height == 0))
    {
        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                          ("%s:crop_rect_params dimensions are zero", __func__), (NULL));
        return GST_FLOW_ERROR;
    }

    /* rectangle for cropped objects */
    crop_rect = cv::Rect(crop_rect_params->left, crop_rect_params->top,
                         crop_rect_params->width, crop_rect_params->height);

    //////////////// IMAGE INSERT RUMMAN ////////////
    // char name[50];
    // cv::Mat image;
    // sprintf(name,"/home/sigmind/Documents/qr.png");
    // image = cv::imread(name,CV_LOAD_IMAGE_COLOR);

    // if(image.empty())
    // {
    //     // std::cout << "Could not read the image: " << image_path << std::endl;
    //     return GST_FLOW_ERROR;
    // }

    // std::cout << "#########\n" << crop_rect.height << " " << crop_rect.width << "#########\n" <<  std::endl;
    // cv::imshow("Display window", image);
    // cv::resize(image, image, cv::Size(in_mat(crop_rect).cols, in_mat(crop_rect).rows));
    // cv::cvtColor(image, image, cv::COLOR_BGR2RGBA);
    // image.copyTo(in_mat(crop_rect));

    /////////////////////////////////////////////////

    /* apply gaussian blur to the detected objects */
    cv::GaussianBlur(in_mat(crop_rect), in_mat(crop_rect), cv::Size(15, 15), 4);

    return GST_FLOW_OK;
}

/**
 * Called when element recieves an input buffer from upstream element.
 */
static GstFlowReturn
gst_dsexample_transform_ip(GstBaseTransform *btrans, GstBuffer *inbuf)
{
    printf("\ntester_again-2 gst_dsexample_transform_ip come from gst_dsexample_class_init method\n");

    GstDsExample *dsexample = GST_DSEXAMPLE(btrans);
    GstMapInfo in_map_info;
    GstFlowReturn flow_ret = GST_FLOW_ERROR;
    gdouble scale_ratio = 1.0;
    DsExampleOutput *output;

    NvBufSurface *surface = NULL;
    NvDsBatchMeta *batch_meta = NULL;
    NvDsFrameMeta *frame_meta = NULL;
    NvDsMetaList *l_frame = NULL;
    guint i = 0;
    guint frameNum;
    dsexample->frame_num++;
    CHECK_CUDA_STATUS(cudaSetDevice(dsexample->gpu_id),
                      "Unable to set cuda device");

    memset(&in_map_info, 0, sizeof(in_map_info));
    if (!gst_buffer_map(inbuf, &in_map_info, GST_MAP_READ))
    {
        g_print("Error: Failed to map gst buffer\n");
        goto error;
    }

    nvds_set_input_system_timestamp(inbuf, GST_ELEMENT_NAME(dsexample));
    surface = (NvBufSurface *)in_map_info.data;
    GST_DEBUG_OBJECT(dsexample,
                     "Processing Frame %" G_GUINT64_FORMAT " Surface %p\n",
                     dsexample->frame_num, surface);

    if (CHECK_NVDS_MEMORY_AND_GPUID(dsexample, surface))
        goto error;

    batch_meta = gst_buffer_get_nvds_batch_meta(inbuf);
    if (batch_meta == nullptr)
    {
        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                          ("NvDsBatchMeta not found for input buffer."), (NULL));
        return GST_FLOW_ERROR;
    }

    if (dsexample->process_full_frame)
    {
        printf("\ncase-1 dsexample process full frame\n");

        int classID;
        for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
             l_frame = l_frame->next)
        {
            frame_meta = (NvDsFrameMeta *)(l_frame->data);
            NvDsMetaList *l_obj = NULL;
            NvDsObjectMeta *obj_meta = NULL;
            for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
                 l_obj = l_obj->next)
            {
                obj_meta = (NvDsObjectMeta *)(l_obj->data);
                int classIDD = (int)obj_meta->class_id;
                // printf(" Class ID found = %d\n", classIDD);
            }

            NvOSD_RectParams rect_params;

            /* Scale the entire frame to processing resolution */
            rect_params.left = 0;
            rect_params.top = 0;
            rect_params.width = dsexample->video_info.width;
            rect_params.height = dsexample->video_info.height;

            /* Scale and convert the frame */
            if (get_converted_mat(dsexample, surface, i, &rect_params,
                                  scale_ratio, dsexample->video_info.width,
                                  dsexample->video_info.height) != GST_FLOW_OK)
            {
                goto error;
            }

            /* Process to get the output */

            // output =
            //     DsExampleProcess(dsexample->dsexamplelib_ctx,
            //                      dsexample->cvmat->data);


            output =
                    DsExampleProcess(dsexample->dsexamplelib_ctx,
                                     dsexample->cvmat); // rumman
            /* Attach the metadata for the full frame */

            g_print("attach_metadata_object 1");
            attach_metadata_object(dsexample, obj_meta, output);

            //g_print("\n Class ID = %d", classID);

            // cv::imwrite("/home/sigmind/Pictures/dsexample/cnt_" + std::to_string(frame_meta->frame_num) + ".jpeg", *dsexample->cvmat);
            //  attach_metadata_full_frame (dsexample, frame_meta, scale_ratio, output, i);
            i++;

            if(output != NULL){
                printf("\n1output is valid and so free\n");
                //                free(output);
            }
            else{
                printf("\n1output is null\n");
            }
        }
    }
    else
    {
        cout<<"\ncase-2 else condit\n";

        /* Using object crops as input to the algorithm. The objects are detected by
     * the primary detector */
        NvDsMetaList *l_obj = NULL;
        NvDsObjectMeta *obj_meta = NULL;

#ifndef __aarch64__
        if (dsexample->blur_objects)
        {
            if (surface->memType != NVBUF_MEM_CUDA_UNIFIED)
            {
                GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                                  ("%s:need NVBUF_MEM_CUDA_UNIFIED memory for opencv blurring", __func__), (NULL));
                return GST_FLOW_ERROR;
            }
        }
#endif

        for (l_frame = batch_meta->frame_meta_list; l_frame != NULL;
             l_frame = l_frame->next)
        {
            frame_meta = (NvDsFrameMeta *)(l_frame->data);
            cv::Mat in_mat;

            if (dsexample->blur_objects)
            {
                cout<<"fst dsexm"<<endl;

                /* Map the buffer so that it can be accessed by CPU */
                if (surface->surfaceList[frame_meta->batch_id].mappedAddr.addr[0] == NULL)
                {
                    if (NvBufSurfaceMap(surface, frame_meta->batch_id, 0, NVBUF_MAP_READ_WRITE) != 0)
                    {
                        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                                          ("%s:buffer map to be accessed by CPU failed", __func__), (NULL));
                        return GST_FLOW_ERROR;
                    }
                }

                /* Cache the mapped data for CPU access */
                NvBufSurfaceSyncForCpu(surface, frame_meta->batch_id, 0);

                in_mat =
                        cv::Mat(surface->surfaceList[frame_meta->batch_id].planeParams.height[0],
                        surface->surfaceList[frame_meta->batch_id].planeParams.width[0], CV_8UC4,
                        surface->surfaceList[frame_meta->batch_id].mappedAddr.addr[0],
                        surface->surfaceList[frame_meta->batch_id].planeParams.pitch[0]);
            }

            for (l_obj = frame_meta->obj_meta_list; l_obj != NULL;
                 l_obj = l_obj->next)
            {
                obj_meta = (NvDsObjectMeta *)(l_obj->data);
                //frameNum = frame_meta->frame_num;

                if (dsexample->blur_objects)
                {

                    ///gaussian blur the detected objects using opencv
                    if (blur_objects(dsexample, frame_meta->batch_id,
                                     &obj_meta->rect_params, in_mat) != GST_FLOW_OK)
                    {
                        cout<<"inside blur call-2 "<<endl;

                        /// Error in blurring, skip processing on object.
                        GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                                          ("blurring the object failed"), (NULL));
                        if (NvBufSurfaceUnMap(surface, frame_meta->batch_id, 0))
                        {
                            GST_ELEMENT_ERROR(dsexample, STREAM, FAILED,
                                              ("%s:buffer unmap to be accessed by CPU failed", __func__), (NULL));
                        }
                        return GST_FLOW_ERROR;
                    }
                    continue;

                }

                /* Should not process on objects smaller than MIN_INPUT_OBJECT_WIDTH x MIN_INPUT_OBJECT_HEIGHT
         * since it will cause hardware scaling issues. */
                if (obj_meta->rect_params.width < MIN_INPUT_OBJECT_WIDTH ||
                        obj_meta->rect_params.height < MIN_INPUT_OBJECT_HEIGHT)
                    continue;

                /* Crop and scale the object */
                if (get_converted_mat(dsexample,
                                      surface, frame_meta->batch_id, &obj_meta->rect_params,
                                      scale_ratio, dsexample->video_info.width,
                                      dsexample->video_info.height) != GST_FLOW_OK)
                {
                    /* Error in conversion, skip processing on object. */
                    continue;
                }

                /* Process the object crop to obtain label */
                // output = DsExampleProcess(dsexample->dsexamplelib_ctx,
                // dsexample->cvmat->data);

                output = DsExampleProcess(dsexample->dsexamplelib_ctx,
                                          dsexample->cvmat);// rumman

//                static int cnt = 0;
//                cv::imwrite("/home/sigmind/Pictures/ds_rawdata3/cnt_" + std::to_string (cnt) + ".jpeg", *output->matrix);
//                cnt++;

                /* Attach labels for the object */
                g_print("attach_metadata_object 2");
                attach_metadata_object(dsexample, obj_meta, output);

                if(output != NULL){
                    printf("\n2output is valid and so free\n");
                    free(output);//johurul
                }
                else if(output == NULL){
                    printf("\n2output is null\n");
                }
            }

            // if (dsexample->blur_objects) {
            /* Cache the mapped data for device access */
            NvBufSurfaceSyncForDevice(surface, frame_meta->batch_id, 0);

            //#ifdef DSEXAMPLE_DEBUG
            /* Use openCV to remove padding and convert RGBA to BGR. Can be skipped if
        * algorithm can handle padded RGBA data. */
            //#if (CV_MAJOR_VERSION >= 4)
            //    cv::cvtColor (in_mat, *dsexample->cvmat, cv::COLOR_RGBA2BGR);
            //#else
            //       cv::cvtColor (in_mat, *dsexample->cvmat, CV_RGBA2BGR);
            //#endif
            /* used to dump the converted mat to files for debug */
            // static guint cnt = 0;
            //cv::imwrite("/home/sigmind/Pictures/dsexample/cnt_" + std::to_string (frame_meta->frame_num) + ".jpeg", *dsexample->cvmat);
            // cnt++;
            //#endif
            // }
        }
    }
    flow_ret = GST_FLOW_OK;

error:

    nvds_set_output_system_timestamp(inbuf, GST_ELEMENT_NAME(dsexample));
    gst_buffer_unmap(inbuf, &in_map_info);
    return flow_ret;
}

/**
 * Attach metadata for the full frame. We will be adding a new metadata.
 */
static void
attach_metadata_full_frame(GstDsExample *dsexample, NvDsFrameMeta *frame_meta,
                           gdouble scale_ratio, DsExampleOutput *output, guint batch_id)
{
    printf("\ntester-11 attach_metadata_full_frame\n");

    NvDsBatchMeta *batch_meta = frame_meta->base_meta.batch_meta;
    NvDsObjectMeta *object_meta = NULL;
    static gchar font_name[] = "Serif";
    GST_DEBUG_OBJECT(dsexample, "Attaching metadata %d\n", output->numObjects);

    for (gint i = 0; i < output->numObjects; i++)
    {
        DsExampleObject *obj = &output->object[i];
        object_meta = nvds_acquire_obj_meta_from_pool(batch_meta);
        NvOSD_RectParams &rect_params = object_meta->rect_params;
        NvOSD_TextParams &text_params = object_meta->text_params;

        /* Assign bounding box coordinates */
        rect_params.left = obj->left;
        rect_params.top = obj->top;
        rect_params.width = obj->width;
        rect_params.height = obj->height;

        /* Semi-transparent yellow background */
        rect_params.has_bg_color = 0;
        rect_params.bg_color = (NvOSD_ColorParams){
                1, 1, 0, 0.4};
        /* Red border of width 6 */
        rect_params.border_width = 3;
        rect_params.border_color = (NvOSD_ColorParams){
                1, 0, 0, 1};

        /* Scale the bounding boxes proportionally based on how the object/frame was
     * scaled during input */
        rect_params.left /= scale_ratio;
        rect_params.top /= scale_ratio;
        rect_params.width /= scale_ratio;
        rect_params.height /= scale_ratio;
        GST_DEBUG_OBJECT(dsexample, "Attaching rect%d of batch%u"
                                    "  left->%f top->%f width->%f"
                                    " height->%f label->%s\n",
                         i, batch_id, rect_params.left,
                         rect_params.top, rect_params.width, rect_params.height, obj->label);

        object_meta->object_id = UNTRACKED_OBJECT_ID;
        g_strlcpy(object_meta->obj_label, obj->label, MAX_LABEL_SIZE);
        /* display_text required heap allocated memory */
        text_params.display_text = g_strdup(obj->label);
        /* Display text above the left top corner of the object */
        text_params.x_offset = rect_params.left;
        text_params.y_offset = rect_params.top - 10;
        /* Set black background for the text */
        text_params.set_bg_clr = 1;
        text_params.text_bg_clr = (NvOSD_ColorParams){
                0, 0, 0, 1};
        /* Font face, size and color */
        text_params.font_params.font_name = font_name;
        text_params.font_params.font_size = 11;
        text_params.font_params.font_color = (NvOSD_ColorParams){
                1, 1, 1, 1};

        nvds_add_obj_meta_to_frame(frame_meta, object_meta, NULL);
        frame_meta->bInferDone = TRUE;
    }
}

/* copy function set by user. "data" holds a pointer to NvDsUserMeta*/
static gpointer
copy_ds_example_meta(gpointer data, gpointer user_data)
{
    printf("\ntester_again-6 copy_ds_example_meta come from attach_metadata_object method\n");
/* new */
//    NvDsUserMeta *user_meta = (NvDsUserMeta *)data;
//    DsExampleOutput *src_user_metadata = (DsExampleOutput *)user_meta->user_meta_data;
//    DsExampleOutput *dst_user_metadata = (DsExampleOutput *)calloc(1, sizeof(DsExampleOutput));
//    memcpy(dst_user_metadata, src_user_metadata, sizeof(DsExampleOutput));
//    return (gpointer)dst_user_metadata;

    /* old */
    NvDsUserMeta *user_meta = (NvDsUserMeta *)data;
    cv::Mat *src_user_metadata = (cv::Mat*)user_meta->user_meta_data;
    cv::Mat *dst_user_metadata = (cv::Mat*)g_malloc0(1000);

    src_user_metadata->copyTo(*dst_user_metadata);
    return (gpointer)dst_user_metadata;

}

/* release function set by user. "data" holds a pointer to NvDsUserMeta*/
static void
release_ds_example_meta(gpointer data, gpointer user_data)
{
    printf("\ntester_again-7 release_ds_example_meta come from attach_metadata_object method\n");

    NvDsUserMeta *user_meta = (NvDsUserMeta *)data;

    cv::Mat *metadata = (cv::Mat*)user_meta->user_meta_data;//johurul
    metadata->release();//johurul

    if (user_meta->user_meta_data)
    {
        printf("\nbefore free user metadata \n");//johurul
//        free(user_meta->user_meta_data);
        g_free(user_meta->user_meta_data);//johurul

        user_meta->user_meta_data = NULL;
    }
}

/**
 * Only update string label in an existing object metadata. No bounding boxes.
 * We assume only one label per object is generated
 */
static void
attach_metadata_object(GstDsExample *dsexample, NvDsObjectMeta *obj_meta,
                       DsExampleOutput *output)
{
    printf("\ntester_again-5 attach_metadata_object come from gst_dsexample_transform_ip method\n");

    printf("\nattach_metadata_object of ??????? gstdsexample.cpp and output->numObjects = %d\n",output->numObjects); // rumman
    //  if (output->numObjects == 0)
    //    return;

    NvDsBatchMeta *batch_meta = obj_meta->base_meta.batch_meta;

    NvDsClassifierMeta *classifier_meta =
            nvds_acquire_classifier_meta_from_pool(batch_meta);

    classifier_meta->unique_component_id = dsexample->unique_id;

    NvDsLabelInfo *label_info =
            nvds_acquire_label_info_meta_from_pool(batch_meta);
    g_strlcpy(label_info->result_label, output->object[0].label, MAX_LABEL_SIZE);
    nvds_add_label_info_meta_to_classifier(classifier_meta, label_info);
    nvds_add_classifier_meta_to_object(obj_meta, classifier_meta);

    ////////////////////////////// rumman //////////////////////////

    nvds_acquire_meta_lock(batch_meta);

    NvDsUserMeta *user_meta = nvds_acquire_user_meta_from_pool(batch_meta);
    NvDsMetaType user_meta_type = NVDS_USER_FRAME_META_EXAMPLE;
    //cv::imwrite("/home/sigmind/Pictures/dsexample/fromds" + std::to_string (countimg) + ".jpeg", *output->matrix);
    //countimg++;

    cv::Mat newFram = *output->matrix;//johurul
    user_meta->user_meta_data = (void *)set_metadata_ptr(newFram);//johurul

    //    static int cnt2 = 0;
    //    cv::imwrite("/home/sigmind/Pictures/ds_rawdata4/cnt_" + std::to_string (cnt2) + ".jpeg", *output->matrix);
    //    cnt2++;

    /* Set NvDsUserMeta below */
//    user_meta->user_meta_data = output; // bhai did differently // user_meta->user_meta_data->matrix

    user_meta->base_meta.meta_type = user_meta_type;
    user_meta->base_meta.copy_func = copy_ds_example_meta;
    user_meta->base_meta.release_func = release_ds_example_meta;

    /* We want to add NvDsUserMeta to frame level */
    nvds_add_user_meta_to_obj(obj_meta, user_meta);

    //////////////////////////////////////////////////////////////////

    //  nvds_acquire_meta_lock(batch_meta);
    NvOSD_TextParams &text_params = obj_meta->text_params;
    NvOSD_RectParams &rect_params = obj_meta->rect_params;

    /* Below code to display the result */
    /* Set black background for the text
   * display_text required heap allocated memory */
    //  if (text_params.display_text)
    //  {
    //    gchar *conc_string = g_strconcat(text_params.display_text, " ",
    //                                     output->object[0].label, NULL);
    //    g_free(text_params.display_text);
    //    text_params.display_text = conc_string;
    //  }
    //  else
    //  {
    //    /* Display text above the left top corner of the object */
    //    text_params.x_offset = rect_params.left;
    //    text_params.y_offset = rect_params.top - 10;
    //    text_params.display_text = g_strdup(output->object[0].label);
    //    /* Font face, size and color */
    //    text_params.font_params.font_name = (char *)"Serif";
    //    text_params.font_params.font_size = 11;
    //    text_params.font_params.font_color = (NvOSD_ColorParams){1, 1, 1, 1};
    //    /* Set black background for the text */
    //    text_params.set_bg_clr = 1;
    //    text_params.text_bg_clr = (NvOSD_ColorParams){
    //        0, 0, 0, 1};
    //  }
    nvds_release_meta_lock(batch_meta);

    printf("\n test-7 after batch release \n");
}

/**
 * Boiler plate for registering a plugin and an element.
 */
static gboolean
dsexample_plugin_init(GstPlugin *plugin)
{
    printf("\ntester-15 dsexample_plugin_init\n");

    GST_DEBUG_CATEGORY_INIT(gst_dsexample_debug, "dsexample", 0,
                            "dsexample plugin");

    return gst_element_register(plugin, "dsexample", GST_RANK_PRIMARY,
                                GST_TYPE_DSEXAMPLE);
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
                  GST_VERSION_MINOR,
                  nvdsgst_dsexample,
                  DESCRIPTION, dsexample_plugin_init, DS_VERSION, LICENSE, BINARY_PACKAGE, URL)
