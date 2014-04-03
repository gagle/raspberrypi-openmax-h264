#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include <string.h>
#include <IL/OMX_Broadcom.h>

const char* dump_OMX_COLOR_FORMATTYPE (OMX_COLOR_FORMATTYPE colorFormat);
const char* dump_OMX_OTHER_FORMATTYPE (OMX_OTHER_FORMATTYPE otherFormat);
const char* dump_OMX_AUDIO_CODINGTYPE (OMX_AUDIO_CODINGTYPE audioCoding);
const char* dump_OMX_VIDEO_CODINGTYPE (OMX_VIDEO_CODINGTYPE videoCoding);
void dump_OMX_PARAM_PORTDEFINITIONTYPE (
    OMX_PARAM_PORTDEFINITIONTYPE* portDefinition);
void dump_OMX_IMAGE_PARAM_PORTFORMATTYPE (
    OMX_IMAGE_PARAM_PORTFORMATTYPE* imagePortFormat);
const char* dump_OMX_STATETYPE (OMX_STATETYPE state);
const char* dump_OMX_ERRORTYPE (OMX_ERRORTYPE error);
const char* dump_OMX_EVENTTYPE (OMX_EVENTTYPE event);
void dump_OMX_BUFFERHEADERTYPE (OMX_BUFFERHEADERTYPE* header);

#endif