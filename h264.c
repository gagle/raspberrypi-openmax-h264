/*
For the sake of simplicity, this example exits on error.

Very quick OpenMAX IL explanation:

- There are components. Each component performs an action. For example, the
  OMX.broadcom.camera module captures images and videos and the
  OMX.broadcom.image_encoder module encodes raw data from an image into multiple
  formats. Each component has input and output ports and receives and sends
  buffers with data. The main goal is to join these components to form a
  pipeline and do complex tasks.
- There are two ways to connect components: with tunnels or manually. The
  non-tunneled ports need to manually allocate the buffers with
  OMX_AllocateBuffer() and free them with OMX_FreeBuffer().
- The components have states.
- There are at least two threads: the thread that uses the application (CPU) and
  the	thread that is used internally by OMX to execute the components (GPU).
- There are two types of functions: blocking and non-blocking. The blocking
  functions are synchronous and the non-blocking are asynchronous. Being
  asynchronous means that the function returns immediately but the result is
  returned in a later time, so you need to wait until you receive an event. This
  example  ses two non-blocking functions: OMX_SendCommand and
  OMX_FillThisBuffer.

Note: The camera component has two video ports: "preview" and "video". The
"preview" port must be enabled even if you don't need it (tunnel it to the
null_sink component).
*/

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include <bcm_host.h>
#include <interface/vcos/vcos.h>
#include <IL/OMX_Broadcom.h>

#include "dump.h"

#define OMX_INIT_STRUCTURE(a) \
  memset (&(a), 0, sizeof (a)); \
  (a).nSize = sizeof (a); \
  (a).nVersion.nVersion = OMX_VERSION; \
  (a).nVersion.s.nVersionMajor = OMX_VERSION_MAJOR; \
  (a).nVersion.s.nVersionMinor = OMX_VERSION_MINOR; \
  (a).nVersion.s.nRevision = OMX_VERSION_REVISION; \
  (a).nVersion.s.nStep = OMX_VERSION_STEP

#define FILENAME "video.h264"

#define VIDEO_FRAMERATE 30
#define VIDEO_BITRATE 10000000
#define VIDEO_CODEC OMX_VIDEO_CodingAVC //H.264/AVC
#define VIDEO_IDR_PERIOD 60 //Minimum 2 (1 IDR frame every 1 frame)

//Some settings doesn't work well
#define CAM_WIDTH 1920
#define CAM_HEIGHT 1080
#define CAM_SHARPNESS 0 //-100 .. 100
#define CAM_CONTRAST 0 //-100 .. 100
#define CAM_BRIGHTNESS 50 //0 .. 100
#define CAM_SATURATION 0 //-100 .. 100
#define CAM_SHUTTER_SPEED 1.0/8.0
#define CAM_SHUTTER_SPEED_AUTO OMX_FALSE
#define CAM_ISO 100 //100 .. 800
#define CAM_ISO_AUTO OMX_TRUE
#define CAM_EXPOSURE OMX_ExposureControlAuto
#define CAM_EXPOSURE_COMPENSATION 0 //-10 .. 10
#define CAM_MIRROR OMX_MirrorNone
#define CAM_ROTATION 0.0 //0.0 90.0 180.0 270.0
#define CAM_COLOR_ENABLE OMX_FALSE
#define CAM_COLOR_U 128 //0 .. 255
#define CAM_COLOR_V 128 //0 .. 255
#define CAM_NOISE_REDUCTION OMX_TRUE
#define CAM_FRAME_STABILIZATION OMX_FALSE
#define CAM_METERING OMX_MeteringModeAverage
#define CAM_WHITE_BALANCE OMX_WhiteBalControlAuto
//The gains are used if white balance is set to off
#define CAM_WHITE_BALANCE_RED_GAIN 0.1 //0.001 .. 7.999
#define CAM_WHITE_BALANCE_BLUE_GAIN 0.1 //0.001 .. 7.999
#define CAM_IMAGE_FILTER OMX_ImageFilterNone

/*
Possible values:

CAM_EXPOSURE
  OMX_ExposureControlOff
  OMX_ExposureControlAuto
  OMX_ExposureControlNight
  OMX_ExposureControlBackLight
  OMX_ExposureControlSpotlight
  OMX_ExposureControlSports
  OMX_ExposureControlSnow
  OMX_ExposureControlBeach
  OMX_ExposureControlLargeAperture
  OMX_ExposureControlSmallAperture
  OMX_ExposureControlVeryLong
  OMX_ExposureControlFixedFps
  OMX_ExposureControlNightWithPreview
  OMX_ExposureControlAntishake
  OMX_ExposureControlFireworks

CAM_IMAGE_FILTER
  OMX_ImageFilterNone
  OMX_ImageFilterNoise
  OMX_ImageFilterEmboss
  OMX_ImageFilterNegative
  OMX_ImageFilterSketch
  OMX_ImageFilterOilPaint
  OMX_ImageFilterHatch
  OMX_ImageFilterGpen
  OMX_ImageFilterAntialias
  OMX_ImageFilterDeRing
  OMX_ImageFilterSolarize
  OMX_ImageFilterWatercolor
  OMX_ImageFilterPastel
  OMX_ImageFilterSharpen
  OMX_ImageFilterFilm
  OMX_ImageFilterBlur
  OMX_ImageFilterSaturation
  OMX_ImageFilterDeInterlaceLineDouble
  OMX_ImageFilterDeInterlaceAdvanced
  OMX_ImageFilterColourSwap
  OMX_ImageFilterWashedOut
  OMX_ImageFilterColourPoint
  OMX_ImageFilterPosterise
  OMX_ImageFilterColourBalance
  OMX_ImageFilterCartoon

CAM_METERING
  OMX_MeteringModeAverage
  OMX_MeteringModeSpot
  OMX_MeteringModeMatrix

CAM_MIRROR
  OMX_MirrorNone
  OMX_MirrorHorizontal
  OMX_MirrorVertical
  OMX_MirrorBoth

CAM_WHITE_BALANCE
  OMX_WhiteBalControlOff
  OMX_WhiteBalControlAuto
  OMX_WhiteBalControlSunLight
  OMX_WhiteBalControlCloudy
  OMX_WhiteBalControlShade
  OMX_WhiteBalControlTungsten
  OMX_WhiteBalControlFluorescent
  OMX_WhiteBalControlIncandescent
  OMX_WhiteBalControlFlash
  OMX_WhiteBalControlHorizon
*/

//Data of each component
typedef struct {
  //The handle is obtained with OMX_GetHandle() and is used on every function
  //that needs to manipulate a component. It is released with OMX_FreeHandle()
  OMX_HANDLETYPE handle;
  //Bitwise OR of flags. Used for blocking the current thread and waiting an
  //event. Used with vcos_event_flags_get() and vcos_event_flags_set()
  VCOS_EVENT_FLAGS_T flags;
  //The fullname of the component
  OMX_STRING name;
} COMPONENT;

//Events used with vcos_event_flags_get() and vcos_event_flags_set()
typedef enum {
  EventError = 0x1,
  EventPortEnable = 0x2,
  EventPortDisable = 0x4,
  EventStateSet = 0x8,
  EventFlush = 0x10,
  EventMarkBuffer = 0x20,
  EventMark = 0x40,
  EventPortSettingsChanged = 0x80,
  EventParamOrConfigChanged = 0x100,
  EventBufferFlag = 0x200,
  EventResourcesAcquired = 0x400,
  EventDynamicResourcesAvailable = 0x800,
  EventFillBufferDone = 0x1000,
  EventEmptyBufferDone = 0x2000,
} EVENT;

//Prototypes
OMX_ERRORTYPE EventHandler (
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_PTR pAppData,
    OMX_IN OMX_EVENTTYPE eEvent,
    OMX_IN OMX_U32 nData1,
    OMX_IN OMX_U32 nData2,
    OMX_IN OMX_PTR pEventData);
OMX_ERRORTYPE FillBufferDone (
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_PTR pAppData,
    OMX_IN OMX_BUFFERHEADERTYPE* pBuffer);
void wake (COMPONENT* component, VCOS_UNSIGNED event);
void wait (
    COMPONENT* component,
    VCOS_UNSIGNED events,
    VCOS_UNSIGNED* retrievedEvents);
void initComponent (COMPONENT* component);
void deinitComponent (COMPONENT* component);
void loadCameraDrivers (COMPONENT* component);
void changeState (COMPONENT* component, OMX_STATETYPE state);
void enablePort (COMPONENT* component, OMX_U32 port);
void disablePort (COMPONENT* component, OMX_U32 port);
void enableEncoderOutputPort (
    COMPONENT* encoder,
    OMX_BUFFERHEADERTYPE** encoderBufferOut);
void disableEncoderOutputPort (
    COMPONENT* encoder,
    OMX_BUFFERHEADERTYPE* encoderBufferOut);
void setCameraSettings (COMPONENT* camera);

//Function that is called when a component receives an event from a secondary
//thread
OMX_ERRORTYPE EventHandler (
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_PTR pAppData,
    OMX_IN OMX_EVENTTYPE eEvent,
    OMX_IN OMX_U32 nData1,
    OMX_IN OMX_U32 nData2,
    OMX_IN OMX_PTR pEventData){
  COMPONENT* component = (COMPONENT*)pAppData;
  
  switch (eEvent){
    case OMX_EventCmdComplete:
      switch (nData1){
        case OMX_CommandStateSet:
          printf ("EVENT: %s, OMX_CommandStateSet, state: %s\n",
              component->name, dump_OMX_STATETYPE (nData2));
          wake (component, EventStateSet);
          break;
        case OMX_CommandPortDisable:
          printf ("EVENT: %s, OMX_CommandPortDisable, port: %d\n",
              component->name, nData2);
          wake (component, EventPortDisable);
          break;
        case OMX_CommandPortEnable:
          printf ("EVENT: %s, OMX_CommandPortEnable, port: %d\n",
              component->name, nData2);
          wake (component, EventPortEnable);
          break;
        case OMX_CommandFlush:
          printf ("EVENT: %s, OMX_CommandFlush, port: %d\n",
              component->name, nData2);
          wake (component, EventFlush);
          break;
        case OMX_CommandMarkBuffer:
          printf ("EVENT: %s, OMX_CommandMarkBuffer, port: %d\n",
              component->name, nData2);
          wake (component, EventMarkBuffer);
          break;
      }
      break;
    case OMX_EventError:
      printf ("EVENT: %s, %s\n", component->name, dump_OMX_ERRORTYPE (nData1));
      wake (component, EventError);
      break;
    case OMX_EventMark:
      printf ("EVENT: %s, OMX_EventMark\n", component->name);
      wake (component, EventMark);
      break;
    case OMX_EventPortSettingsChanged:
      printf ("EVENT: %s, OMX_EventPortSettingsChanged, port: %d\n",
          component->name, nData1);
      wake (component, EventPortSettingsChanged);
      break;
    case OMX_EventParamOrConfigChanged:
      printf ("EVENT: %s, OMX_EventParamOrConfigChanged, nData1: %d, nData2: "
          "%X\n", component->name, nData1, nData2);
      wake (component, EventParamOrConfigChanged);
      break;
    case OMX_EventBufferFlag:
      printf ("EVENT: %s, OMX_EventBufferFlag, port: %d\n",
          component->name, nData1);
      wake (component, EventBufferFlag);
      break;
    case OMX_EventResourcesAcquired:
      printf ("EVENT: %s, OMX_EventResourcesAcquired\n", component->name);
      wake (component, EventResourcesAcquired);
      break;
    case OMX_EventDynamicResourcesAvailable:
      printf ("EVENT: %s, OMX_EventDynamicResourcesAvailable\n",
          component->name);
      wake (component, EventDynamicResourcesAvailable);
      break;
    default:
      //This should never execute, just ignore
      printf ("EVENT: %s, Unknown (%X)\n", eEvent);
      break;
  }

  return OMX_ErrorNone;
}

//Function that is called when a component fills a buffer with data
OMX_ERRORTYPE FillBufferDone (
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_PTR pAppData,
    OMX_IN OMX_BUFFERHEADERTYPE* pBuffer){
  COMPONENT* component = (COMPONENT*)pAppData;
  
  printf ("EVENT: %s, FillBufferDone\n", component->name);
  wake (component, EventFillBufferDone);
  
  return OMX_ErrorNone;
}

void wake (COMPONENT* component, VCOS_UNSIGNED event){
  vcos_event_flags_set (&component->flags, event, VCOS_OR);
}

void wait (
    COMPONENT* component,
    VCOS_UNSIGNED events,
    VCOS_UNSIGNED* retrievedEvents){
  VCOS_UNSIGNED set;
  if (vcos_event_flags_get (&component->flags, events | EventError,
      VCOS_OR_CONSUME, VCOS_SUSPEND, &set)){
    printf ("ERROR: vcos_event_flags_get\n");
    exit (1);
  }
  if (set == EventError){
    exit (1);
  }
  if (retrievedEvents){
    *retrievedEvents = set;
  }
}

void initComponent (COMPONENT* component){
  printf ("Initializing component %s\n", component->name);
  
  OMX_ERRORTYPE error;
  
  //Create the event flags
  if (vcos_event_flags_create (&component->flags, "component")){
    printf ("ERROR: vcos_event_flags_create\n");
    exit (1);
  }
  
  //Each component has an EventHandler and FillBufferDone functions
  OMX_CALLBACKTYPE callbacks;
  callbacks.EventHandler = EventHandler;
  callbacks.FillBufferDone = FillBufferDone;
  
  //Get the handle
  if (error = OMX_GetHandle (&component->handle, component->name, component,
      &callbacks)){
    printf ("ERROR: OMX_GetHandle: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Disable all the ports
  OMX_INDEXTYPE types[] = {
    OMX_IndexParamAudioInit,
    OMX_IndexParamVideoInit,
    OMX_IndexParamImageInit,
    OMX_IndexParamOtherInit
  };
  OMX_PORT_PARAM_TYPE ports;
  OMX_INIT_STRUCTURE (ports);

  int i;
  for (i=0; i<4; i++){
    if (error = OMX_GetParameter (component->handle, types[i], &ports)){
      printf ("ERROR: OMX_GetParameter: %s\n", dump_OMX_ERRORTYPE (error));
      exit (1);
    }
    
    OMX_U32 port;
    VCOS_UNSIGNED retrievedEvents;
    for (port=ports.nStartPortNumber;
        port<ports.nStartPortNumber + ports.nPorts; port++){
      //Disable the port
      disablePort (component, port);
      //Wait to the event
      wait (component, EventPortDisable, NULL);
    }
  }
}

void deinitComponent (COMPONENT* component){
  printf ("Deinitializing component %s\n", component->name);
  
  OMX_ERRORTYPE error;
  
  vcos_event_flags_delete (&component->flags);

  if (error = OMX_FreeHandle (component->handle)){
    printf ("ERROR: OMX_FreeHandle: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

void loadCameraDrivers (COMPONENT* component){
  /*
  This is a specific behaviour of the Broadcom's Raspberry Pi OpenMAX IL
  implementation module because the OMX_SetConfig() and OMX_SetParameter() are
  blocking functions but the drivers are loaded asynchronously, that is, an
  event is fired to signal the completion. Basically, what you're saying is:
  
  "When the parameter with index OMX_IndexParamCameraDeviceNumber is set, load
  the camera drivers and emit an OMX_EventParamOrConfigChanged event"
  
  The red LED of the camera will be turned on after this call.
  */
  
  printf ("Loading camera drivers\n");
  
  OMX_ERRORTYPE error;

  OMX_CONFIG_REQUESTCALLBACKTYPE cbs;
  OMX_INIT_STRUCTURE (cbs);
  cbs.nPortIndex = OMX_ALL;
  cbs.nIndex = OMX_IndexParamCameraDeviceNumber;
  cbs.bEnable = OMX_TRUE;
  if (error = OMX_SetConfig (component->handle, OMX_IndexConfigRequestCallback,
      &cbs)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  OMX_PARAM_U32TYPE device;
  OMX_INIT_STRUCTURE (device);
  device.nPortIndex = OMX_ALL;
  //ID for the camera device
  device.nU32 = 0;
  if (error = OMX_SetParameter (component->handle,
      OMX_IndexParamCameraDeviceNumber, &device)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  wait (component, EventParamOrConfigChanged, NULL);
}

void changeState (COMPONENT* component, OMX_STATETYPE state){
  printf ("Changing %s state to %s\n", component->name,
      dump_OMX_STATETYPE (state));
  
  OMX_ERRORTYPE error;
  
  if (error = OMX_SendCommand (component->handle, OMX_CommandStateSet, state,
      NULL)){
    printf ("ERROR: OMX_SendCommand: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

void enablePort (COMPONENT* component, OMX_U32 port){
  printf ("Enabling port %d (%s)\n", port, component->name);
  
  OMX_ERRORTYPE error;
  
  if (error = OMX_SendCommand (component->handle, OMX_CommandPortEnable,
      port, NULL)){
    printf ("ERROR: OMX_SendCommand: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

void disablePort (COMPONENT* component, OMX_U32 port){
  printf ("Disabling port %d (%s)\n", port, component->name);
  
  OMX_ERRORTYPE error;
  
  if (error = OMX_SendCommand (component->handle, OMX_CommandPortDisable,
      port, NULL)){
    printf ("ERROR: OMX_SendCommand: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

void enableEncoderOutputPort (
    COMPONENT* encoder,
    OMX_BUFFERHEADERTYPE** encoderBufferOut){
  //The port is not enabled until the buffer is allocated
  OMX_ERRORTYPE error;
  
  enablePort (encoder, 201);
  
  OMX_PARAM_PORTDEFINITIONTYPE encoderPortDef;
  OMX_INIT_STRUCTURE (encoderPortDef);
  encoderPortDef.nPortIndex = 201;
  if (error = OMX_GetParameter (encoder->handle, OMX_IndexParamPortDefinition,
      &encoderPortDef)){
    printf ("ERROR: OMX_GetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  printf ("Allocating %s output buffer\n", encoder->name);
  if (error = OMX_AllocateBuffer (encoder->handle, encoderBufferOut, 201, NULL,
      encoderPortDef.nBufferSize)){
    printf ("ERROR: OMX_AllocateBuffer: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  wait (encoder, EventPortEnable, NULL);
}

void disableEncoderOutputPort (
    COMPONENT* encoder,
    OMX_BUFFERHEADERTYPE* encoderBufferOut){
  //The port is not disabled until the buffer is released
  OMX_ERRORTYPE error;
  
  disablePort (encoder, 201);
  
  //Free encoder output buffer
  printf ("Releasing %s output buffer\n", encoder->name);
  if (error = OMX_FreeBuffer (encoder->handle, 201, encoderBufferOut)){
    printf ("ERROR: OMX_FreeBuffer: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  wait (encoder, EventPortDisable, NULL);
}

void setCameraSettings (COMPONENT* camera){
  printf ("Configuring camera settings\n");

  OMX_ERRORTYPE error;
  
  //Sharpness
  OMX_CONFIG_SHARPNESSTYPE sharpness;
  OMX_INIT_STRUCTURE (sharpness);
  sharpness.nPortIndex = OMX_ALL;
  sharpness.nSharpness = CAM_SHARPNESS;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonSharpness,
      &sharpness)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Contrast
  OMX_CONFIG_CONTRASTTYPE contrast;
  OMX_INIT_STRUCTURE (contrast);
  contrast.nPortIndex = OMX_ALL;
  contrast.nContrast = CAM_CONTRAST;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonContrast,
      &contrast)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Saturation
  OMX_CONFIG_SATURATIONTYPE saturation;
  OMX_INIT_STRUCTURE (saturation);
  saturation.nPortIndex = OMX_ALL;
  saturation.nSaturation = CAM_SATURATION;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonSaturation,
      &saturation)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Brightness
  OMX_CONFIG_BRIGHTNESSTYPE brightness;
  OMX_INIT_STRUCTURE (brightness);
  brightness.nPortIndex = OMX_ALL;
  brightness.nBrightness = CAM_BRIGHTNESS;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonBrightness,
      &brightness)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Exposure value
  OMX_CONFIG_EXPOSUREVALUETYPE exposureValue;
  OMX_INIT_STRUCTURE (exposureValue);
  exposureValue.nPortIndex = OMX_ALL;
  exposureValue.eMetering = CAM_METERING;
  exposureValue.xEVCompensation =
      (OMX_S32)((CAM_EXPOSURE_COMPENSATION<<16)/6.0);
  exposureValue.nShutterSpeedMsec = (OMX_U32)((CAM_SHUTTER_SPEED)*1e6);
  exposureValue.bAutoShutterSpeed = CAM_SHUTTER_SPEED_AUTO;
  exposureValue.nSensitivity = CAM_ISO;
  exposureValue.bAutoSensitivity = CAM_ISO_AUTO;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonExposureValue,
      &exposureValue)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Exposure control
  OMX_CONFIG_EXPOSURECONTROLTYPE exposureControl;
  OMX_INIT_STRUCTURE (exposureControl);
  exposureControl.nPortIndex = OMX_ALL;
  exposureControl.eExposureControl = CAM_EXPOSURE;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonExposure,
      &exposureControl)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Frame stabilisation
  OMX_CONFIG_FRAMESTABTYPE frameStabilisation;
  OMX_INIT_STRUCTURE (frameStabilisation);
  frameStabilisation.nPortIndex = OMX_ALL;
  frameStabilisation.bStab = CAM_FRAME_STABILIZATION;
  if (error = OMX_SetConfig (camera->handle,
      OMX_IndexConfigCommonFrameStabilisation, &frameStabilisation)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //White balance
  OMX_CONFIG_WHITEBALCONTROLTYPE whiteBalance;
  OMX_INIT_STRUCTURE (whiteBalance);
  whiteBalance.nPortIndex = OMX_ALL;
  whiteBalance.eWhiteBalControl = CAM_WHITE_BALANCE;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonWhiteBalance,
      &whiteBalance)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //White balance gains (if white balance is set to off)
  if (!CAM_WHITE_BALANCE){
    OMX_CONFIG_CUSTOMAWBGAINSTYPE whiteBalanceGains;
    OMX_INIT_STRUCTURE (whiteBalanceGains);
    whiteBalanceGains.xGainR = (OMX_U32)(CAM_WHITE_BALANCE_RED_GAIN*65536);
    whiteBalanceGains.xGainB = (OMX_U32)(CAM_WHITE_BALANCE_BLUE_GAIN*65536);
    if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCustomAwbGains,
        &whiteBalanceGains)){
      printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
      exit (1);
    }
  }
  //Image filter
  OMX_CONFIG_IMAGEFILTERTYPE imageFilter;
  OMX_INIT_STRUCTURE (imageFilter);
  imageFilter.nPortIndex = OMX_ALL;
  imageFilter.eImageFilter = CAM_IMAGE_FILTER;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonImageFilter,
      &imageFilter)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Mirror
  OMX_CONFIG_MIRRORTYPE mirror;
  OMX_INIT_STRUCTURE (mirror);
  mirror.nPortIndex = 72;
  mirror.eMirror = CAM_MIRROR;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonMirror,
      &mirror)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Rotation
  OMX_CONFIG_ROTATIONTYPE rotation;
  OMX_INIT_STRUCTURE (rotation);
  rotation.nPortIndex = 72;
  rotation.nRotation = CAM_ROTATION;
  if (error = OMX_SetConfig (camera->handle, OMX_IndexConfigCommonRotate,
      &rotation)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Color enhancement
  OMX_CONFIG_COLORENHANCEMENTTYPE colorEnhancement;
  OMX_INIT_STRUCTURE (colorEnhancement);
  colorEnhancement.nPortIndex = OMX_ALL;
  colorEnhancement.bColorEnhancement = CAM_COLOR_ENABLE;
  colorEnhancement.nCustomizedU = CAM_COLOR_U;
  colorEnhancement.nCustomizedV = CAM_COLOR_V;
  if (error = OMX_SetConfig (camera->handle,
      OMX_IndexConfigCommonColorEnhancement, &colorEnhancement)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  //Denoise
  OMX_CONFIG_BOOLEANTYPE denoise;
  OMX_INIT_STRUCTURE (denoise);
  denoise.bEnabled = CAM_NOISE_REDUCTION;
  if (error = OMX_SetConfig (camera->handle,
      OMX_IndexConfigStillColourDenoiseEnable, &denoise)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

void setH264Settings (COMPONENT* encoder){
  OMX_ERRORTYPE error;
  
  //Configure bitrate
  printf ("Configuring %s bitrate\n", encoder->name);
  OMX_VIDEO_PARAM_BITRATETYPE bitrate;
  OMX_INIT_STRUCTURE (bitrate);
  bitrate.eControlRate = OMX_Video_ControlRateVariable;
  bitrate.nTargetBitrate = VIDEO_BITRATE;
  bitrate.nPortIndex = 201;
  if (error = OMX_SetParameter (encoder->handle, OMX_IndexParamVideoBitrate,
      &bitrate)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Configure codec
  printf ("Configuring %s codec\n", encoder->name);
  OMX_VIDEO_PARAM_PORTFORMATTYPE format;
  OMX_INIT_STRUCTURE (format);
  format.nPortIndex = 201;
  format.eCompressionFormat = VIDEO_CODEC;
  if (error = OMX_SetParameter (encoder->handle, OMX_IndexParamVideoPortFormat,
      &format)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Configure IDR period
  OMX_VIDEO_CONFIG_AVCINTRAPERIOD idr;
  OMX_INIT_STRUCTURE (idr);
  idr.nPortIndex = 201;
  if (error = OMX_GetConfig (encoder->handle,
      OMX_IndexConfigVideoAVCIntraPeriod, &idr)){
    printf ("ERROR: OMX_GetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  idr.nIDRPeriod = VIDEO_IDR_PERIOD;
  if (error = OMX_SetConfig (encoder->handle,
      OMX_IndexConfigVideoAVCIntraPeriod, &idr)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
}

int main (){
  OMX_ERRORTYPE error;
  OMX_BUFFERHEADERTYPE* encoderBufferOut;
  OMX_BUFFERHEADERTYPE* cameraBufferOut;
  COMPONENT camera;
  COMPONENT encoder;
  COMPONENT nullSink;
  camera.name = "OMX.broadcom.camera";
  encoder.name = "OMX.broadcom.video_encode";
  nullSink.name = "OMX.broadcom.null_sink";
  
  //Open the file
  int fd = open (FILENAME, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
  if (fd == -1){
    printf ("ERROR: open\n");
    exit (1);
  }
  
  //Initialize Broadcom's VideoCore APIs
  bcm_host_init ();
  
  //Initialize OpenMAX IL
  if (error = OMX_Init ()){
    printf ("ERROR: OMX_Init: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Initialize components
  initComponent (&camera);
  initComponent (&encoder);
  initComponent (&nullSink);
  
  //Initialize camera drivers
  loadCameraDrivers (&camera);
  
  //Configure camera port definition
  printf ("Configuring %s port definition\n", camera.name);
  OMX_PARAM_PORTDEFINITIONTYPE portDefinition;
  OMX_INIT_STRUCTURE (portDefinition);
  portDefinition.nPortIndex = 71;
  if (error = OMX_GetParameter (camera.handle, OMX_IndexParamPortDefinition,
      &portDefinition)){
    printf ("ERROR: OMX_GetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  portDefinition.format.video.nFrameWidth = CAM_WIDTH;
  portDefinition.format.video.nFrameHeight = CAM_HEIGHT;
  //Stride is byte-per-pixel*width, YUV has 1 byte per pixel, so the stride is
  //the width. See mmal/util/mmal_util.c, mmal_encoding_width_to_stride()
  portDefinition.format.video.nStride = CAM_WIDTH;
  portDefinition.format.video.xFramerate = VIDEO_FRAMERATE << 16;
  portDefinition.format.video.eCompressionFormat = OMX_VIDEO_CodingUnused;
  portDefinition.format.video.eColorFormat = OMX_COLOR_FormatYUV420PackedPlanar;
  if (error = OMX_SetParameter (camera.handle, OMX_IndexParamPortDefinition,
      &portDefinition)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Preview port
  portDefinition.nPortIndex = 70;
  if (error = OMX_SetParameter (camera.handle, OMX_IndexParamPortDefinition,
      &portDefinition)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  printf ("Configuring %s framerate\n", camera.name);
  OMX_CONFIG_FRAMERATETYPE framerate;
  OMX_INIT_STRUCTURE (framerate);
  framerate.nPortIndex = 71;
  framerate.xEncodeFramerate = portDefinition.format.video.xFramerate;
  if (error = OMX_SetConfig (camera.handle, OMX_IndexConfigVideoFramerate,
      &framerate)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Preview port
  framerate.nPortIndex = 70;
  if (error = OMX_SetConfig (camera.handle, OMX_IndexConfigVideoFramerate,
      &framerate)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Configure camera settings
  setCameraSettings (&camera);
  
  //Configure encoder port definition
  printf ("Configuring %s port definition\n", encoder.name);
  OMX_INIT_STRUCTURE (portDefinition);
  portDefinition.nPortIndex = 201;
  if ((error = OMX_GetParameter (encoder.handle, OMX_IndexParamPortDefinition,
      &portDefinition))){
    printf ("ERROR: OMX_GetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  portDefinition.format.video.nFrameWidth = CAM_WIDTH;
  portDefinition.format.video.nFrameHeight = CAM_HEIGHT;
  portDefinition.format.video.nStride = CAM_WIDTH;
  portDefinition.format.video.xFramerate = VIDEO_FRAMERATE << 16;
  //Despite being configured later, these two fields need to be set
  portDefinition.format.video.nBitrate = VIDEO_BITRATE;
  portDefinition.format.video.eCompressionFormat = VIDEO_CODEC;
  if (error = OMX_SetParameter (encoder.handle, OMX_IndexParamPortDefinition,
      &portDefinition)){
    printf ("ERROR: OMX_SetParameter: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Configure H264
  setH264Settings (&encoder);
  
  //Setup tunnels: camera (video) -> video_encode, camera (preview) -> null_sink
  printf ("Configuring tunnels\n");
  if (error = OMX_SetupTunnel (camera.handle, 71, encoder.handle, 200)){
    printf ("ERROR: OMX_SetupTunnel: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  if (error = OMX_SetupTunnel (camera.handle, 70, nullSink.handle, 240)){
    printf ("ERROR: OMX_SetupTunnel: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Change state to IDLE
  changeState (&camera, OMX_StateIdle);
  wait (&camera, EventStateSet, NULL);
  changeState (&encoder, OMX_StateIdle);
  wait (&encoder, EventStateSet, NULL);
  changeState (&nullSink, OMX_StateIdle);
  wait (&nullSink, EventStateSet, NULL);
  
  //Enable the ports
  enablePort (&camera, 71);
  wait (&camera, EventPortEnable, NULL);
  enablePort (&camera, 70);
  wait (&camera, EventPortEnable, NULL);
  enablePort (&nullSink, 240);
  wait (&nullSink, EventPortEnable, NULL);
  enablePort (&encoder, 200);
  wait (&encoder, EventPortEnable, NULL);
  enableEncoderOutputPort (&encoder, &encoderBufferOut);
  
  //Change state to EXECUTING
  changeState (&camera, OMX_StateExecuting);
  wait (&camera, EventStateSet, NULL);
  changeState (&encoder, OMX_StateExecuting);
  wait (&encoder, EventStateSet, NULL);
  wait (&encoder, EventPortSettingsChanged, NULL);
  changeState (&nullSink, OMX_StateExecuting);
  wait (&nullSink, EventStateSet, NULL);
  
  //Enable camera capture port. This basically says that the port 71 will be
  //used to get data from the camera. If you're capturing a still, the port 72
  //must be used
  printf ("Enabling %s capture port\n", camera.name);
  OMX_CONFIG_PORTBOOLEANTYPE cameraCapturePort;
  OMX_INIT_STRUCTURE (cameraCapturePort);
  cameraCapturePort.nPortIndex = 71;
  cameraCapturePort.bEnabled = OMX_TRUE;
  if (error = OMX_SetConfig (camera.handle, OMX_IndexConfigPortCapturing,
      &cameraCapturePort)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Record ~3000 ms
  struct timespec spec;
  clock_gettime (CLOCK_MONOTONIC, &spec);
  long now = spec.tv_sec*1000 + spec.tv_nsec/1.0e6;
  long end = now + 3000;
  
  while (1){
    //Get the buffer data
    if (error = OMX_FillThisBuffer (encoder.handle, encoderBufferOut)){
      printf ("ERROR: OMX_FillThisBuffer: %s\n", dump_OMX_ERRORTYPE (error));
      exit (1);
    }
    
    //Wait until it's filled
    wait (&encoder, EventFillBufferDone, NULL);
    
    //Append the buffer into the file
    if (pwrite (fd, encoderBufferOut->pBuffer, encoderBufferOut->nFilledLen,
        encoderBufferOut->nOffset) == -1){
      printf ("ERROR: pwrite\n");
      exit (1);
    }
    
    clock_gettime (CLOCK_MONOTONIC, &spec);
    if (spec.tv_sec*1000 + spec.tv_nsec/1.0e6 >= end) break;
  }
  
  printf ("------------------------------------------------\n");
  
  //Disable camera capture port
  printf ("Disabling %s capture port\n", camera.name);
  cameraCapturePort.bEnabled = OMX_FALSE;
  if (error = OMX_SetConfig (camera.handle, OMX_IndexConfigPortCapturing,
      &cameraCapturePort)){
    printf ("ERROR: OMX_SetConfig: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Change state to IDLE
  changeState (&camera, OMX_StateIdle);
  wait (&camera, EventStateSet, NULL);
  changeState (&encoder, OMX_StateIdle);
  wait (&encoder, EventStateSet, NULL);
  changeState (&nullSink, OMX_StateIdle);
  wait (&nullSink, EventStateSet, NULL);
  
  //Disable the tunnel ports
  disablePort (&camera, 71);
  wait (&camera, EventPortDisable, NULL);
  disablePort (&camera, 70);
  wait (&camera, EventPortDisable, NULL);
  disablePort (&nullSink, 240);
  wait (&nullSink, EventPortDisable, NULL);
  disablePort (&encoder, 200);
  wait (&encoder, EventPortDisable, NULL);
  disableEncoderOutputPort (&encoder, encoderBufferOut);
  
  //Change state to LOADED
  changeState (&camera, OMX_StateLoaded);
  wait (&camera, EventStateSet, NULL);
  changeState (&encoder, OMX_StateLoaded);
  wait (&encoder, EventStateSet, NULL);
  changeState (&nullSink, OMX_StateLoaded);
  wait (&nullSink, EventStateSet, NULL);
  
  //Deinitialize components
  deinitComponent (&camera);
  deinitComponent (&encoder);
  deinitComponent (&nullSink);
  
  //Deinitialize OpenMAX IL
  if (error = OMX_Deinit ()){
    printf ("ERROR: OMX_Deinit: %s\n", dump_OMX_ERRORTYPE (error));
    exit (1);
  }
  
  //Deinitialize Broadcom's VideoCore APIs
  bcm_host_deinit ();
  
  //Close the file
  if (close (fd)){
    printf ("ERROR: close\n");
    exit (1);
  }
  
  printf ("ok\n");
  
  return 0;
}