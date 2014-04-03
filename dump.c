#include "dump.h"

const char* dump_OMX_COLOR_FORMATTYPE (OMX_COLOR_FORMATTYPE colorFormat){
  switch (colorFormat){
    case OMX_COLOR_FormatUnused:
      return "OMX_COLOR_FormatUnused";
    case OMX_COLOR_FormatMonochrome:
      return "OMX_COLOR_FormatMonochrome";
    case OMX_COLOR_Format8bitRGB332:
      return "OMX_COLOR_Format8bitRGB332";
    case OMX_COLOR_Format12bitRGB444:
      return "OMX_COLOR_Format12bitRGB444";
    case OMX_COLOR_Format16bitARGB4444:
      return "OMX_COLOR_Format16bitARGB4444";
    case OMX_COLOR_Format16bitARGB1555:
      return "OMX_COLOR_Format16bitARGB1555";
    case OMX_COLOR_Format16bitRGB565:
      return "OMX_COLOR_Format16bitRGB565";
    case OMX_COLOR_Format16bitBGR565:
      return "OMX_COLOR_Format16bitBGR565";
    case OMX_COLOR_Format18bitRGB666:
      return "OMX_COLOR_Format18bitRGB666";
    case OMX_COLOR_Format18bitARGB1665:
      return "OMX_COLOR_Format18bitARGB1665";
    case OMX_COLOR_Format19bitARGB1666:
      return "OMX_COLOR_Format19bitARGB1666";
    case OMX_COLOR_Format24bitRGB888:
      return "OMX_COLOR_Format24bitRGB888";
    case OMX_COLOR_Format24bitBGR888:
      return "OMX_COLOR_Format24bitBGR888";
    case OMX_COLOR_Format24bitARGB1887:
      return "OMX_COLOR_Format24bitARGB1887";
    case OMX_COLOR_Format25bitARGB1888:
      return "OMX_COLOR_Format25bitARGB1888";
    case OMX_COLOR_Format32bitBGRA8888:
      return "OMX_COLOR_Format32bitBGRA8888";
    case OMX_COLOR_Format32bitARGB8888:
      return "OMX_COLOR_Format32bitARGB8888";
    case OMX_COLOR_FormatYUV411Planar:
      return "OMX_COLOR_FormatYUV411Planar";
    case OMX_COLOR_FormatYUV411PackedPlanar:
      return "OMX_COLOR_FormatYUV411PackedPlanar";
    case OMX_COLOR_FormatYUV420Planar:
      return "OMX_COLOR_FormatYUV420Planar";
    case OMX_COLOR_FormatYUV420PackedPlanar:
      return "OMX_COLOR_FormatYUV420PackedPlanar";
    case OMX_COLOR_FormatYUV420SemiPlanar:
      return "OMX_COLOR_FormatYUV420SemiPlanar";
    case OMX_COLOR_FormatYUV422Planar:
      return "OMX_COLOR_FormatYUV422Planar";
    case OMX_COLOR_FormatYUV422PackedPlanar:
      return "OMX_COLOR_FormatYUV422PackedPlanar";
    case OMX_COLOR_FormatYUV422SemiPlanar:
      return "OMX_COLOR_FormatYUV422SemiPlanar";
    case OMX_COLOR_FormatYCbYCr:
      return "OMX_COLOR_FormatYCbYCr";
    case OMX_COLOR_FormatYCrYCb:
      return "OMX_COLOR_FormatYCrYCb";
    case OMX_COLOR_FormatCbYCrY:
      return "OMX_COLOR_FormatCbYCrY";
    case OMX_COLOR_FormatCrYCbY:
      return "OMX_COLOR_FormatCrYCbY";
    case OMX_COLOR_FormatYUV444Interleaved:
      return "OMX_COLOR_FormatYUV444Interleaved";
    case OMX_COLOR_FormatRawBayer8bit:
      return "OMX_COLOR_FormatRawBayer8bit";
    case OMX_COLOR_FormatRawBayer10bit:
      return "OMX_COLOR_FormatRawBayer10bit";
    case OMX_COLOR_FormatRawBayer8bitcompressed:
      return "OMX_COLOR_FormatRawBayer8bitcompressed";
    case OMX_COLOR_FormatL2:
      return "OMX_COLOR_FormatL2";
    case OMX_COLOR_FormatL4:
      return "OMX_COLOR_FormatL4";
    case OMX_COLOR_FormatL8:
      return "OMX_COLOR_FormatL8";
    case OMX_COLOR_FormatL16:
      return "OMX_COLOR_FormatL16";
    case OMX_COLOR_FormatL24:
      return "OMX_COLOR_FormatL24";
    case OMX_COLOR_FormatL32:
      return "OMX_COLOR_FormatL32";
    case OMX_COLOR_FormatYUV420PackedSemiPlanar:
      return "OMX_COLOR_FormatYUV420PackedSemiPlanar";
    case OMX_COLOR_FormatYUV422PackedSemiPlanar:
      return "OMX_COLOR_FormatYUV422PackedSemiPlanar";
    case OMX_COLOR_Format18BitBGR666:
      return "OMX_COLOR_Format18BitBGR666";
    case OMX_COLOR_Format24BitARGB6666:
      return "OMX_COLOR_Format24BitARGB6666";
    case OMX_COLOR_Format24BitABGR6666:
      return "OMX_COLOR_Format24BitABGR6666";
    case OMX_COLOR_Format32bitABGR8888:
      return "OMX_COLOR_Format32bitABGR8888";
    case OMX_COLOR_Format8bitPalette:
      return "OMX_COLOR_Format8bitPalette";
    case OMX_COLOR_FormatYUVUV128:
      return "OMX_COLOR_FormatYUVUV128";
    case OMX_COLOR_FormatRawBayer12bit:
      return "OMX_COLOR_FormatRawBayer12bit";
    case OMX_COLOR_FormatBRCMEGL:
      return "OMX_COLOR_FormatBRCMEGL";
    case OMX_COLOR_FormatBRCMOpaque:
      return "OMX_COLOR_FormatBRCMOpaque";
    case OMX_COLOR_FormatYVU420PackedPlanar:
      return "OMX_COLOR_FormatYVU420PackedPlanar";
    case OMX_COLOR_FormatYVU420PackedSemiPlanar:
      return "OMX_COLOR_FormatYVU420PackedSemiPlanar";
    default:
      return "unkown";
  }
}

const char* dump_OMX_OTHER_FORMATTYPE (OMX_OTHER_FORMATTYPE otherFormat){
  switch (otherFormat){
    case OMX_OTHER_FormatTime:
      return "OMX_OTHER_FormatTime";
    case OMX_OTHER_FormatPower:
      return "OMX_OTHER_FormatPower";
    case OMX_OTHER_FormatStats:
      return "OMX_OTHER_FormatStats";
    case OMX_OTHER_FormatBinary:
      return "OMX_OTHER_FormatBinary";
    case OMX_OTHER_FormatText:
      return "OMX_OTHER_FormatText";
    case OMX_OTHER_FormatText3GP5:
      return "OMX_OTHER_FormatText3GP5";
    default:
      return "unkown";
  }
}

const char* dump_OMX_AUDIO_CODINGTYPE (OMX_AUDIO_CODINGTYPE audioCoding){
  switch (audioCoding){
    case OMX_AUDIO_CodingUnused:
      return "OMX_AUDIO_CodingUnused";
    case OMX_AUDIO_CodingAutoDetect:
      return "OMX_AUDIO_CodingAutoDetect";
    case OMX_AUDIO_CodingPCM:
      return "OMX_AUDIO_CodingPCM";
    case OMX_AUDIO_CodingADPCM:
      return "OMX_AUDIO_CodingADPCM";
    case OMX_AUDIO_CodingAMR:
      return "OMX_AUDIO_CodingAMR";
    case OMX_AUDIO_CodingGSMFR:
      return "OMX_AUDIO_CodingGSMFR";
    case OMX_AUDIO_CodingGSMEFR:
      return "OMX_AUDIO_CodingGSMEFR";
    case OMX_AUDIO_CodingGSMHR:
      return "OMX_AUDIO_CodingGSMHR";
    case OMX_AUDIO_CodingPDCFR:
      return "OMX_AUDIO_CodingPDCFR";
    case OMX_AUDIO_CodingPDCEFR:
      return "OMX_AUDIO_CodingPDCEFR";
    case OMX_AUDIO_CodingPDCHR:
      return "OMX_AUDIO_CodingPDCHR";
    case OMX_AUDIO_CodingTDMAFR:
      return "OMX_AUDIO_CodingTDMAFR";
    case OMX_AUDIO_CodingTDMAEFR:
      return "OMX_AUDIO_CodingTDMAEFR";
    case OMX_AUDIO_CodingQCELP8:
      return "OMX_AUDIO_CodingQCELP8";
    case OMX_AUDIO_CodingQCELP13:
      return "OMX_AUDIO_CodingQCELP13";
    case OMX_AUDIO_CodingEVRC:
      return "OMX_AUDIO_CodingEVRC";
    case OMX_AUDIO_CodingSMV:
      return "OMX_AUDIO_CodingSMV";
    case OMX_AUDIO_CodingG711:
      return "OMX_AUDIO_CodingG711";
    case OMX_AUDIO_CodingG723:
      return "OMX_AUDIO_CodingG723";
    case OMX_AUDIO_CodingG726:
      return "OMX_AUDIO_CodingG726";
    case OMX_AUDIO_CodingG729:
      return "OMX_AUDIO_CodingG729";
    case OMX_AUDIO_CodingAAC:
      return "OMX_AUDIO_CodingAAC";
    case OMX_AUDIO_CodingMP3:
      return "OMX_AUDIO_CodingMP3";
    case OMX_AUDIO_CodingSBC:
      return "OMX_AUDIO_CodingSBC";
    case OMX_AUDIO_CodingVORBIS:
      return "OMX_AUDIO_CodingVORBIS";
    case OMX_AUDIO_CodingWMA:
      return "OMX_AUDIO_CodingWMA";
    case OMX_AUDIO_CodingRA:
      return "OMX_AUDIO_CodingRA";
    case OMX_AUDIO_CodingMIDI:
      return "OMX_AUDIO_CodingMIDI";
    case OMX_AUDIO_CodingFLAC:
      return "OMX_AUDIO_CodingFLAC";
    case OMX_AUDIO_CodingDTS:
      return "OMX_AUDIO_CodingDTS";
    case OMX_AUDIO_CodingWMAPRO:
      return "OMX_AUDIO_CodingWMAPRO";
    case OMX_AUDIO_CodingATRAC3:
      return "OMX_AUDIO_CodingATRAC3";
    case OMX_AUDIO_CodingATRACX:
      return "OMX_AUDIO_CodingATRACX";
    case OMX_AUDIO_CodingATRACAAL:
      return "OMX_AUDIO_CodingATRACAAL";
    default:
      return "unknown";
  }
}

const char* dump_OMX_VIDEO_CODINGTYPE (OMX_VIDEO_CODINGTYPE videoCoding){
  switch (videoCoding){
    case OMX_VIDEO_CodingUnused:
      return "OMX_VIDEO_CodingUnused";
    case OMX_VIDEO_CodingAutoDetect:
      return "OMX_VIDEO_CodingAutoDetect";
    case OMX_VIDEO_CodingMPEG2:
      return "OMX_VIDEO_CodingMPEG2";
    case OMX_VIDEO_CodingH263:
      return "OMX_VIDEO_CodingH263";
    case OMX_VIDEO_CodingMPEG4:
      return "OMX_VIDEO_CodingMPEG4";
    case OMX_VIDEO_CodingWMV:
      return "OMX_VIDEO_CodingWMV";
    case OMX_VIDEO_CodingRV:
      return "OMX_VIDEO_CodingRV";
    case OMX_VIDEO_CodingAVC:
      return "OMX_VIDEO_CodingAVC";
    case OMX_VIDEO_CodingMJPEG:
      return "OMX_VIDEO_CodingMJPEG";
    case OMX_VIDEO_CodingVP6:
      return "OMX_VIDEO_CodingVP6";
    case OMX_VIDEO_CodingVP7:
      return "OMX_VIDEO_CodingVP7";
    case OMX_VIDEO_CodingVP8:
      return "OMX_VIDEO_CodingVP8";
    case OMX_VIDEO_CodingYUV:
      return "OMX_VIDEO_CodingYUV";
    case OMX_VIDEO_CodingSorenson:
      return "OMX_VIDEO_CodingSorenson";
    case OMX_VIDEO_CodingTheora:
      return "OMX_VIDEO_CodingTheora";
    case OMX_VIDEO_CodingMVC:
      return "OMX_VIDEO_CodingMVC";
    default:
      return "unknown";
  }
}

const char* dump_OMX_IMAGE_CODINGTYPE (OMX_IMAGE_CODINGTYPE imageCoding){
  switch (imageCoding){
    case OMX_IMAGE_CodingUnused:
      return "OMX_IMAGE_CodingUnused";
    case OMX_IMAGE_CodingAutoDetect:
      return "OMX_IMAGE_CodingAutoDetect";
    case OMX_IMAGE_CodingJPEG:
      return "OMX_IMAGE_CodingJPEG";
    case OMX_IMAGE_CodingJPEG2K:
      return "OMX_IMAGE_CodingJPEG2K";
    case OMX_IMAGE_CodingEXIF:
      return "OMX_IMAGE_CodingEXIF";
    case OMX_IMAGE_CodingTIFF:
      return "OMX_IMAGE_CodingTIFF";
    case OMX_IMAGE_CodingGIF:
      return "OMX_IMAGE_CodingGIF";
    case OMX_IMAGE_CodingPNG:
      return "OMX_IMAGE_CodingPNG";
    case OMX_IMAGE_CodingLZW:
      return "OMX_IMAGE_CodingLZW";
    case OMX_IMAGE_CodingBMP:
      return "OMX_IMAGE_CodingBMP";
    case OMX_IMAGE_CodingTGA:
      return "OMX_IMAGE_CodingTGA";
    case OMX_IMAGE_CodingPPM:
      return "OMX_IMAGE_CodingPPM";
    default:
      return "unknown";
  }
}

void dump_OMX_PARAM_PORTDEFINITIONTYPE (
    OMX_PARAM_PORTDEFINITIONTYPE* portDefinition){
  char domain[512];
  char domainInfo[512];
  
  switch (portDefinition->eDomain){
    case OMX_PortDomainAudio:
      strcpy (domain, "OMX_PortDomainAudio");
      sprintf (domainInfo,
          "    cMIMEType: %s\n"
          "    bFlagErrorConcealment: %s\n"
          "    eEncoding: %s\n",
          portDefinition->format.video.cMIMEType,
          portDefinition->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_AUDIO_CODINGTYPE (
              portDefinition->format.audio.eEncoding));
      break;
    case OMX_PortDomainVideo:
      strcpy (domain, "OMX_PortDomainVideo");
      sprintf (domainInfo,
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
          , portDefinition->format.video.cMIMEType,
          portDefinition->format.video.nFrameWidth,
          portDefinition->format.video.nFrameHeight,
          portDefinition->format.video.nStride,
          portDefinition->format.video.nSliceHeight,
          portDefinition->format.video.nBitrate,
          portDefinition->format.video.xFramerate,
          portDefinition->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_VIDEO_CODINGTYPE (
              portDefinition->format.video.eCompressionFormat),
          dump_OMX_COLOR_FORMATTYPE (
              portDefinition->format.video.eColorFormat));
      break;
    case OMX_PortDomainImage:
      strcpy (domain, "OMX_PortDomainImage");
      sprintf (domainInfo,
          "    cMIMEType: %s\n"
          "    nFrameWidth: %d\n"
          "    nFrameHeight: %d\n"
          "    nStride: %d\n"
          "    nSliceHeight: %d\n"
          "    bFlagErrorConcealment: %s\n"
          "    eCompressionFormat: %s\n"
          "    eColorFormat: %s\n"
          , portDefinition->format.image.cMIMEType,
          portDefinition->format.image.nFrameWidth,
          portDefinition->format.image.nFrameHeight,
          portDefinition->format.image.nStride,
          portDefinition->format.image.nSliceHeight,
          portDefinition->format.image.bFlagErrorConcealment ? "true" : "false",
          dump_OMX_IMAGE_CODINGTYPE (
              portDefinition->format.image.eCompressionFormat),
          dump_OMX_COLOR_FORMATTYPE (
              portDefinition->format.image.eColorFormat));
      break;
    case OMX_PortDomainOther:
      strcpy (domain, "OMX_PortDomainOther");
      sprintf (domainInfo,
          "    eFormat: %s\n",
          dump_OMX_OTHER_FORMATTYPE (
              portDefinition->format.other.eFormat));
      break;
    default:
      strcpy (domain, "unknown");
      strcpy (domainInfo, "    unknown");
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
      portDefinition->nSize,
      portDefinition->nPortIndex,
      portDefinition->eDir == OMX_DirInput ? "input" : "output",
      portDefinition->nBufferCountActual,
      portDefinition->nBufferCountMin,
      portDefinition->nBufferSize,
      portDefinition->bEnabled ? "true" : "false",
      portDefinition->bPopulated ? "true" : "false",
      domain,
      domainInfo,
      portDefinition->bBuffersContiguous ? "true": "false",
      portDefinition->nBufferAlignment);
}

void dump_OMX_IMAGE_PARAM_PORTFORMATTYPE (
    OMX_IMAGE_PARAM_PORTFORMATTYPE* imagePortFormat){
  printf (
      "nSize: %d\n"
      "nPortIndex: %d\n"
      "nIndex: %d\n"
      "eCompressionFormat: %s\n"
      "eColorFormat: %s\n",
      imagePortFormat->nSize,
      imagePortFormat->nPortIndex,
      imagePortFormat->nIndex,
      dump_OMX_IMAGE_CODINGTYPE (imagePortFormat->eCompressionFormat),
      dump_OMX_COLOR_FORMATTYPE (imagePortFormat->eColorFormat));
}

const char* dump_OMX_STATETYPE (OMX_STATETYPE state){
  switch (state){
    case OMX_StateInvalid: return "OMX_StateInvalid";			
    case OMX_StateLoaded: return "OMX_StateLoaded";			
    case OMX_StateIdle: return "OMX_StateIdle";			
    case OMX_StateExecuting: return "OMX_StateExecuting";			
    case OMX_StatePause: return "OMX_StatePause";			
    case OMX_StateWaitForResources: return "OMX_StateWaitForResources";
    default: return "unknown";
  }
}

const char* dump_OMX_ERRORTYPE (OMX_ERRORTYPE error){
  switch (error){
    case OMX_ErrorNone:
      return "OMX_ErrorNone";
    case OMX_ErrorInsufficientResources:
      return "OMX_ErrorInsufficientResources";
    case OMX_ErrorUndefined:
      return "OMX_ErrorUndefined";
    case OMX_ErrorInvalidComponentName:
      return "OMX_ErrorInvalidComponentName";
    case OMX_ErrorComponentNotFound:
      return "OMX_ErrorComponentNotFound";
    case OMX_ErrorInvalidComponent:
      return "OMX_ErrorInvalidComponent";
    case OMX_ErrorBadParameter:
      return "OMX_ErrorBadParameter";
    case OMX_ErrorNotImplemented:
      return "OMX_ErrorNotImplemented";
    case OMX_ErrorUnderflow:
      return "OMX_ErrorUnderflow";
    case OMX_ErrorOverflow:
      return "OMX_ErrorOverflow";
    case OMX_ErrorHardware:
      return "OMX_ErrorHardware";
    case OMX_ErrorInvalidState:
      return "OMX_ErrorInvalidState";
    case OMX_ErrorStreamCorrupt:
      return "OMX_ErrorStreamCorrupt";
    case OMX_ErrorPortsNotCompatible:
      return "OMX_ErrorPortsNotCompatible";
    case OMX_ErrorResourcesLost:
      return "OMX_ErrorResourcesLost";
    case OMX_ErrorNoMore:
      return "OMX_ErrorNoMore";
    case OMX_ErrorVersionMismatch:
      return "OMX_ErrorVersionMismatch";
    case OMX_ErrorNotReady:
      return "OMX_ErrorNotReady";
    case OMX_ErrorTimeout:
      return "OMX_ErrorTimeout";
    case OMX_ErrorSameState:
      return "OMX_ErrorSameState";
    case OMX_ErrorResourcesPreempted:
      return "OMX_ErrorResourcesPreempted";
    case OMX_ErrorPortUnresponsiveDuringAllocation:
      return "OMX_ErrorPortUnresponsiveDuringAllocation";
    case OMX_ErrorPortUnresponsiveDuringDeallocation:
      return "OMX_ErrorPortUnresponsiveDuringDeallocation";
    case OMX_ErrorPortUnresponsiveDuringStop:
      return "OMX_ErrorPortUnresponsiveDuringStop";
    case OMX_ErrorIncorrectStateTransition:
      return "OMX_ErrorIncorrectStateTransition";
    case OMX_ErrorIncorrectStateOperation:
      return "OMX_ErrorIncorrectStateOperation";
    case OMX_ErrorUnsupportedSetting:
      return "OMX_ErrorUnsupportedSetting";
    case OMX_ErrorUnsupportedIndex:
      return "OMX_ErrorUnsupportedIndex";
    case OMX_ErrorBadPortIndex:
      return "OMX_ErrorBadPortIndex";
    case OMX_ErrorPortUnpopulated:
      return "OMX_ErrorPortUnpopulated";
    case OMX_ErrorComponentSuspended:
      return "OMX_ErrorComponentSuspended";
    case OMX_ErrorDynamicResourcesUnavailable:
      return "OMX_ErrorDynamicResourcesUnavailable";
    case OMX_ErrorMbErrorsInFrame:
      return "OMX_ErrorMbErrorsInFrame";
    case OMX_ErrorFormatNotDetected:
      return "OMX_ErrorFormatNotDetected";
    case OMX_ErrorContentPipeOpenFailed:
      return "OMX_ErrorContentPipeOpenFailed";
    case OMX_ErrorContentPipeCreationFailed:
      return "OMX_ErrorContentPipeCreationFailed";
    case OMX_ErrorSeperateTablesUsed:
      return "OMX_ErrorSeperateTablesUsed";
    case OMX_ErrorTunnelingUnsupported:
      return "OMX_ErrorTunnelingUnsupported";
    case OMX_ErrorDiskFull:
      return "OMX_ErrorDiskFull";
    case OMX_ErrorMaxFileSize:
      return "OMX_ErrorMaxFileSize";
    case OMX_ErrorDrmUnauthorised:
      return "OMX_ErrorDrmUnauthorised";
    case OMX_ErrorDrmExpired:
      return "OMX_ErrorDrmExpired";
    case OMX_ErrorDrmGeneral:
      return "OMX_ErrorDrmGeneral";
    default:
      return "unknown";
  }
}

const char* dump_OMX_EVENTTYPE (OMX_EVENTTYPE event){
  switch (event){
    case OMX_EventCmdComplete:
      return "OMX_EventCmdComplete";
    case OMX_EventError:
      return "OMX_EventError";
    case OMX_EventMark:
      return "OMX_EventMark";
    case OMX_EventPortSettingsChanged:
      return "OMX_EventPortSettingsChanged";
    case OMX_EventBufferFlag:
      return "OMX_EventBufferFlag";
    case OMX_EventResourcesAcquired:
      return "OMX_EventResourcesAcquired";
    case OMX_EventComponentResumed:
      return "OMX_EventComponentResumed";
    case OMX_EventDynamicResourcesAvailable:
      return "OMX_EventDynamicResourcesAvailable";
    case OMX_EventPortFormatDetected:
      return "OMX_EventPortFormatDetected";
    case OMX_EventParamOrConfigChanged:
      return "OMX_EventParamOrConfigChanged";
    default:
      return "unkonwn";
  }
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