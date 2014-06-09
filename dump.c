#include "dump.h"

#define DUMP_CASE(x) case x: return #x;

const char* dump_OMX_COLOR_FORMATTYPE (OMX_COLOR_FORMATTYPE color){
  switch (color){
    DUMP_CASE (OMX_COLOR_FormatUnused)
    DUMP_CASE (OMX_COLOR_FormatMonochrome)
    DUMP_CASE (OMX_COLOR_Format8bitRGB332)
    DUMP_CASE (OMX_COLOR_Format12bitRGB444)
    DUMP_CASE (OMX_COLOR_Format16bitARGB4444)
    DUMP_CASE (OMX_COLOR_Format16bitARGB1555)
    DUMP_CASE (OMX_COLOR_Format16bitRGB565)
    DUMP_CASE (OMX_COLOR_Format16bitBGR565)
    DUMP_CASE (OMX_COLOR_Format18bitRGB666)
    DUMP_CASE (OMX_COLOR_Format18bitARGB1665)
    DUMP_CASE (OMX_COLOR_Format19bitARGB1666)
    DUMP_CASE (OMX_COLOR_Format24bitRGB888)
    DUMP_CASE (OMX_COLOR_Format24bitBGR888)
    DUMP_CASE (OMX_COLOR_Format24bitARGB1887)
    DUMP_CASE (OMX_COLOR_Format25bitARGB1888)
    DUMP_CASE (OMX_COLOR_Format32bitBGRA8888)
    DUMP_CASE (OMX_COLOR_Format32bitARGB8888)
    DUMP_CASE (OMX_COLOR_FormatYUV411Planar)
    DUMP_CASE (OMX_COLOR_FormatYUV411PackedPlanar)
    DUMP_CASE (OMX_COLOR_FormatYUV420Planar)
    DUMP_CASE (OMX_COLOR_FormatYUV420PackedPlanar)
    DUMP_CASE (OMX_COLOR_FormatYUV420SemiPlanar)
    DUMP_CASE (OMX_COLOR_FormatYUV422Planar)
    DUMP_CASE (OMX_COLOR_FormatYUV422PackedPlanar)
    DUMP_CASE (OMX_COLOR_FormatYUV422SemiPlanar)
    DUMP_CASE (OMX_COLOR_FormatYCbYCr)
    DUMP_CASE (OMX_COLOR_FormatYCrYCb)
    DUMP_CASE (OMX_COLOR_FormatCbYCrY)
    DUMP_CASE (OMX_COLOR_FormatCrYCbY)
    DUMP_CASE (OMX_COLOR_FormatYUV444Interleaved)
    DUMP_CASE (OMX_COLOR_FormatRawBayer8bit)
    DUMP_CASE (OMX_COLOR_FormatRawBayer10bit)
    DUMP_CASE (OMX_COLOR_FormatRawBayer8bitcompressed)
    DUMP_CASE (OMX_COLOR_FormatL2)
    DUMP_CASE (OMX_COLOR_FormatL4)
    DUMP_CASE (OMX_COLOR_FormatL8)
    DUMP_CASE (OMX_COLOR_FormatL16)
    DUMP_CASE (OMX_COLOR_FormatL24)
    DUMP_CASE (OMX_COLOR_FormatL32)
    DUMP_CASE (OMX_COLOR_FormatYUV420PackedSemiPlanar)
    DUMP_CASE (OMX_COLOR_FormatYUV422PackedSemiPlanar)
    DUMP_CASE (OMX_COLOR_Format18BitBGR666)
    DUMP_CASE (OMX_COLOR_Format24BitARGB6666)
    DUMP_CASE (OMX_COLOR_Format24BitABGR6666)
    DUMP_CASE (OMX_COLOR_Format32bitABGR8888)
    DUMP_CASE (OMX_COLOR_Format8bitPalette)
    DUMP_CASE (OMX_COLOR_FormatYUVUV128)
    DUMP_CASE (OMX_COLOR_FormatRawBayer12bit)
    DUMP_CASE (OMX_COLOR_FormatBRCMEGL)
    DUMP_CASE (OMX_COLOR_FormatBRCMOpaque)
    DUMP_CASE (OMX_COLOR_FormatYVU420PackedPlanar)
    DUMP_CASE (OMX_COLOR_FormatYVU420PackedSemiPlanar)
    default: return "unknown OMX_COLOR_FORMATTYPE";
  }
}

const char* dump_OMX_OTHER_FORMATTYPE (OMX_OTHER_FORMATTYPE format){
  switch (format){
    DUMP_CASE (OMX_OTHER_FormatTime);
    DUMP_CASE (OMX_OTHER_FormatPower);
    DUMP_CASE (OMX_OTHER_FormatStats);
    DUMP_CASE (OMX_OTHER_FormatBinary);
    DUMP_CASE (OMX_OTHER_FormatText);
    DUMP_CASE (OMX_OTHER_FormatTextSKM2);
    DUMP_CASE (OMX_OTHER_FormatText3GP5);
    default: return "unknown OMX_OTHER_FORMATTYPE";
  }
}

const char* dump_OMX_AUDIO_CODINGTYPE (OMX_AUDIO_CODINGTYPE coding){
  switch (coding){
    DUMP_CASE (OMX_AUDIO_CodingUnused)
    DUMP_CASE (OMX_AUDIO_CodingAutoDetect)
    DUMP_CASE (OMX_AUDIO_CodingPCM)
    DUMP_CASE (OMX_AUDIO_CodingADPCM)
    DUMP_CASE (OMX_AUDIO_CodingAMR)
    DUMP_CASE (OMX_AUDIO_CodingGSMFR)
    DUMP_CASE (OMX_AUDIO_CodingGSMEFR)
    DUMP_CASE (OMX_AUDIO_CodingGSMHR)
    DUMP_CASE (OMX_AUDIO_CodingPDCFR)
    DUMP_CASE (OMX_AUDIO_CodingPDCEFR)
    DUMP_CASE (OMX_AUDIO_CodingPDCHR)
    DUMP_CASE (OMX_AUDIO_CodingTDMAFR)
    DUMP_CASE (OMX_AUDIO_CodingTDMAEFR)
    DUMP_CASE (OMX_AUDIO_CodingQCELP8)
    DUMP_CASE (OMX_AUDIO_CodingQCELP13)
    DUMP_CASE (OMX_AUDIO_CodingEVRC)
    DUMP_CASE (OMX_AUDIO_CodingSMV)
    DUMP_CASE (OMX_AUDIO_CodingG711)
    DUMP_CASE (OMX_AUDIO_CodingG723)
    DUMP_CASE (OMX_AUDIO_CodingG726)
    DUMP_CASE (OMX_AUDIO_CodingG729)
    DUMP_CASE (OMX_AUDIO_CodingAAC)
    DUMP_CASE (OMX_AUDIO_CodingMP3)
    DUMP_CASE (OMX_AUDIO_CodingSBC)
    DUMP_CASE (OMX_AUDIO_CodingVORBIS)
    DUMP_CASE (OMX_AUDIO_CodingWMA)
    DUMP_CASE (OMX_AUDIO_CodingRA)
    DUMP_CASE (OMX_AUDIO_CodingMIDI)
    DUMP_CASE (OMX_AUDIO_CodingFLAC)
    DUMP_CASE (OMX_AUDIO_CodingDDP)
    DUMP_CASE (OMX_AUDIO_CodingDTS)
    DUMP_CASE (OMX_AUDIO_CodingWMAPRO)
    DUMP_CASE (OMX_AUDIO_CodingATRAC3)
    DUMP_CASE (OMX_AUDIO_CodingATRACX)
    DUMP_CASE (OMX_AUDIO_CodingATRACAAL)
    default: return "unknown OMX_AUDIO_CODINGTYPE";
  }
}

const char* dump_OMX_VIDEO_CODINGTYPE (OMX_VIDEO_CODINGTYPE coding){
  switch (coding){
    DUMP_CASE (OMX_VIDEO_CodingUnused)
    DUMP_CASE (OMX_VIDEO_CodingAutoDetect)
    DUMP_CASE (OMX_VIDEO_CodingMPEG2)
    DUMP_CASE (OMX_VIDEO_CodingH263)
    DUMP_CASE (OMX_VIDEO_CodingMPEG4)
    DUMP_CASE (OMX_VIDEO_CodingWMV)
    DUMP_CASE (OMX_VIDEO_CodingRV)
    DUMP_CASE (OMX_VIDEO_CodingAVC)
    DUMP_CASE (OMX_VIDEO_CodingMJPEG)
    DUMP_CASE (OMX_VIDEO_CodingVP6)
    DUMP_CASE (OMX_VIDEO_CodingVP7)
    DUMP_CASE (OMX_VIDEO_CodingVP8)
    DUMP_CASE (OMX_VIDEO_CodingYUV)
    DUMP_CASE (OMX_VIDEO_CodingSorenson)
    DUMP_CASE (OMX_VIDEO_CodingTheora)
    DUMP_CASE (OMX_VIDEO_CodingMVC)
    default: return "unknown OMX_VIDEO_CODINGTYPE";
  }
}

const char* dump_OMX_IMAGE_CODINGTYPE (OMX_IMAGE_CODINGTYPE coding){
  switch (coding){
    DUMP_CASE (OMX_IMAGE_CodingUnused)
    DUMP_CASE (OMX_IMAGE_CodingAutoDetect)
    DUMP_CASE (OMX_IMAGE_CodingJPEG)
    DUMP_CASE (OMX_IMAGE_CodingJPEG2K)
    DUMP_CASE (OMX_IMAGE_CodingEXIF)
    DUMP_CASE (OMX_IMAGE_CodingTIFF)
    DUMP_CASE (OMX_IMAGE_CodingGIF)
    DUMP_CASE (OMX_IMAGE_CodingPNG)
    DUMP_CASE (OMX_IMAGE_CodingLZW)
    DUMP_CASE (OMX_IMAGE_CodingBMP)
    DUMP_CASE (OMX_IMAGE_CodingTGA)
    DUMP_CASE (OMX_IMAGE_CodingPPM)
    default: return "unknown OMX_IMAGE_CODINGTYPE";
  }
}

const char* dump_OMX_STATETYPE (OMX_STATETYPE state){
  switch (state){
    DUMP_CASE (OMX_StateInvalid)
    DUMP_CASE (OMX_StateLoaded)
    DUMP_CASE (OMX_StateIdle)
    DUMP_CASE (OMX_StateExecuting)
    DUMP_CASE (OMX_StatePause)
    DUMP_CASE (OMX_StateWaitForResources)
    default: return "unknown OMX_STATETYPE";
  }
}

const char* dump_OMX_ERRORTYPE (OMX_ERRORTYPE error){
  switch (error){
    DUMP_CASE (OMX_ErrorNone)
    DUMP_CASE (OMX_ErrorInsufficientResources)
    DUMP_CASE (OMX_ErrorUndefined)
    DUMP_CASE (OMX_ErrorInvalidComponentName)
    DUMP_CASE (OMX_ErrorComponentNotFound)
    DUMP_CASE (OMX_ErrorInvalidComponent)
    DUMP_CASE (OMX_ErrorBadParameter)
    DUMP_CASE (OMX_ErrorNotImplemented)
    DUMP_CASE (OMX_ErrorUnderflow)
    DUMP_CASE (OMX_ErrorOverflow)
    DUMP_CASE (OMX_ErrorHardware)
    DUMP_CASE (OMX_ErrorInvalidState)
    DUMP_CASE (OMX_ErrorStreamCorrupt)
    DUMP_CASE (OMX_ErrorPortsNotCompatible)
    DUMP_CASE (OMX_ErrorResourcesLost)
    DUMP_CASE (OMX_ErrorNoMore)
    DUMP_CASE (OMX_ErrorVersionMismatch)
    DUMP_CASE (OMX_ErrorNotReady)
    DUMP_CASE (OMX_ErrorTimeout)
    DUMP_CASE (OMX_ErrorSameState)
    DUMP_CASE (OMX_ErrorResourcesPreempted)
    DUMP_CASE (OMX_ErrorPortUnresponsiveDuringAllocation)
    DUMP_CASE (OMX_ErrorPortUnresponsiveDuringDeallocation)
    DUMP_CASE (OMX_ErrorPortUnresponsiveDuringStop)
    DUMP_CASE (OMX_ErrorIncorrectStateTransition)
    DUMP_CASE (OMX_ErrorIncorrectStateOperation)
    DUMP_CASE (OMX_ErrorUnsupportedSetting)
    DUMP_CASE (OMX_ErrorUnsupportedIndex)
    DUMP_CASE (OMX_ErrorBadPortIndex)
    DUMP_CASE (OMX_ErrorPortUnpopulated)
    DUMP_CASE (OMX_ErrorComponentSuspended)
    DUMP_CASE (OMX_ErrorDynamicResourcesUnavailable)
    DUMP_CASE (OMX_ErrorMbErrorsInFrame)
    DUMP_CASE (OMX_ErrorFormatNotDetected)
    DUMP_CASE (OMX_ErrorContentPipeOpenFailed)
    DUMP_CASE (OMX_ErrorContentPipeCreationFailed)
    DUMP_CASE (OMX_ErrorSeperateTablesUsed)
    DUMP_CASE (OMX_ErrorTunnelingUnsupported)
    DUMP_CASE (OMX_ErrorDiskFull)
    DUMP_CASE (OMX_ErrorMaxFileSize)
    DUMP_CASE (OMX_ErrorDrmUnauthorised)
    DUMP_CASE (OMX_ErrorDrmExpired)
    DUMP_CASE (OMX_ErrorDrmGeneral)
    default: return "unknown OMX_ERRORTYPE";
  }
}

const char* dump_OMX_EVENTTYPE (OMX_EVENTTYPE event){
  switch (event){
    DUMP_CASE (OMX_EventCmdComplete)
    DUMP_CASE (OMX_EventError)
    DUMP_CASE (OMX_EventMark)
    DUMP_CASE (OMX_EventPortSettingsChanged)
    DUMP_CASE (OMX_EventBufferFlag)
    DUMP_CASE (OMX_EventResourcesAcquired)
    DUMP_CASE (OMX_EventComponentResumed)
    DUMP_CASE (OMX_EventDynamicResourcesAvailable)
    DUMP_CASE (OMX_EventPortFormatDetected)
    DUMP_CASE (OMX_EventParamOrConfigChanged)
    default: return "unkonwn OMX_EVENTTYPE";
  }
}

const char* dump_OMX_INDEXTYPE (OMX_INDEXTYPE type){
  switch (type){
    DUMP_CASE (OMX_IndexParamAudioInit)
    DUMP_CASE (OMX_IndexParamVideoInit)
    DUMP_CASE (OMX_IndexParamImageInit)
    DUMP_CASE (OMX_IndexParamOtherInit)
    default: return "other OMX_INDEXTYPE";
  }
}

void dump_OMX_PARAM_PORTDEFINITIONTYPE (
    OMX_PARAM_PORTDEFINITIONTYPE* port){
  char domain[512];
  char domain_info[512];
  
  switch (port->eDomain){
    case OMX_PortDomainAudio:
      strcpy (domain, "OMX_PortDomainAudio");
      sprintf (domain_info,
          "    cMIMEType: %s\n"
          "    bFlagErrorConcealment: %s\n"
          "    eEncoding: %s\n",
          port->format.video.cMIMEType,
          port->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_AUDIO_CODINGTYPE (
              port->format.audio.eEncoding));
      break;
    case OMX_PortDomainVideo:
      strcpy (domain, "OMX_PortDomainVideo");
      sprintf (domain_info,
          "    cMIMEType: %s\n"
          "    nFrameWidth: %d\n"
          "    nFrameHeight: %d\n"
          "    nStride: %d\n"
          "    nSliceHeight: %d\n"
          "    nBitrate: %d\n"
          "    xFramerate: %d\n"
          "    bFlagErrorConcealment: %s\n"
          "    eCompressionFormat: %s\n"
          "    eColorFormat: %s\n"
          , port->format.video.cMIMEType,
          port->format.video.nFrameWidth,
          port->format.video.nFrameHeight,
          port->format.video.nStride,
          port->format.video.nSliceHeight,
          port->format.video.nBitrate,
          port->format.video.xFramerate,
          port->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_VIDEO_CODINGTYPE (
              port->format.video.eCompressionFormat),
          dump_OMX_COLOR_FORMATTYPE (
              port->format.video.eColorFormat));
      break;
    case OMX_PortDomainImage:
      strcpy (domain, "OMX_PortDomainImage");
      sprintf (domain_info,
          "    cMIMEType: %s\n"
          "    nFrameWidth: %d\n"
          "    nFrameHeight: %d\n"
          "    nStride: %d\n"
          "    nSliceHeight: %d\n"
          "    bFlagErrorConcealment: %s\n"
          "    eCompressionFormat: %s\n"
          "    eColorFormat: %s\n"
          , port->format.image.cMIMEType,
          port->format.image.nFrameWidth,
          port->format.image.nFrameHeight,
          port->format.image.nStride,
          port->format.image.nSliceHeight,
          port->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_IMAGE_CODINGTYPE (
              port->format.image.eCompressionFormat),
          dump_OMX_COLOR_FORMATTYPE (
              port->format.image.eColorFormat));
      break;
    case OMX_PortDomainOther:
      strcpy (domain, "OMX_PortDomainOther");
      sprintf (domain_info,
          "    eFormat: %s\n",
          dump_OMX_OTHER_FORMATTYPE (
              port->format.other.eFormat));
      break;
    default:
      strcpy (domain, "unknown");
      strcpy (domain_info, "    unknown");
      break;
  }
  
  printf (
      "nSize: %d\n"
      "nPortIndex: %d\n"
      "eDir: %s\n"
      "nBufferCountActual: %d\n"
      "nBufferCountMin: %d\n"
      "nBufferSize: %d\n"
      "bEnabled: %s\n"
      "bPopulated: %s\n"
      "eDomain: %s\n"
      "  format:\n"
      "%s"
      "bBuffersContiguous: %s\n"
      "nBufferAlignment: %d\n",
      port->nSize,
      port->nPortIndex,
      port->eDir == OMX_DirInput ? "input" : "output",
      port->nBufferCountActual,
      port->nBufferCountMin,
      port->nBufferSize,
      port->bEnabled ? "true" : "false",
      port->bPopulated ? "true" : "false",
      domain,
      domain_info,
      port->bBuffersContiguous ? "true": "false",
      port->nBufferAlignment);
}

void dump_OMX_IMAGE_PARAM_PORTFORMATTYPE (
    OMX_IMAGE_PARAM_PORTFORMATTYPE* port){
  printf (
      "nSize: %d\n"
      "nPortIndex: %d\n"
      "nIndex: %d\n"
      "eCompressionFormat: %s\n"
      "eColorFormat: %s\n",
      port->nSize,
      port->nPortIndex,
      port->nIndex,
      dump_OMX_IMAGE_CODINGTYPE (port->eCompressionFormat),
      dump_OMX_COLOR_FORMATTYPE (port->eColorFormat));
}

void dump_OMX_BUFFERHEADERTYPE (OMX_BUFFERHEADERTYPE* header){
  long long int timestamp = (long long int)header->nTimeStamp.nHighPart;
  timestamp = timestamp << 32;
  timestamp |= (long long int)header->nTimeStamp.nLowPart;

  printf (
      "nSize: %d\n"
      "nAllocLen: %d\n"
      "nFilledLen: %d\n"
      "nOffset: %d\n"
      "hMarkTargetComponent: %s\n"
      "nTickCount: %d\n"
      "nTimeStamp: %lld\n"
      "nFlags: %X\n"
      "nOutputPortIndex: %d\n"
      "nInputPortIndex: %d\n",
      header->nSize,
      header->nAllocLen,
      header->nFilledLen,
      header->nOffset,
      header->hMarkTargetComponent ? "not null" : "null (no mark)",
      header->nTickCount,
      timestamp,
      header->nFlags,
      header->nOutputPortIndex,
      header->nInputPortIndex);
}