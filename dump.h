#ifndef DUMP_H
#define DUMP_H

#include <stdio.h>
#include <string.h>
#include <IL/OMX_Broadcom.h>

const char* dump_OMX_COLOR_FORMATTYPE (OMX_COLOR_FORMATTYPE color);
const char* dump_OMX_OTHER_FORMATTYPE (OMX_OTHER_FORMATTYPE format);
const char* dump_OMX_AUDIO_CODINGTYPE (OMX_AUDIO_CODINGTYPE coding);
const char* dump_OMX_VIDEO_CODINGTYPE (OMX_VIDEO_CODINGTYPE coding);
const char* dump_OMX_IMAGE_CODINGTYPE (OMX_IMAGE_CODINGTYPE coding);
const char* dump_OMX_STATETYPE (OMX_STATETYPE state);
const char* dump_OMX_ERRORTYPE (OMX_ERRORTYPE error);
const char* dump_OMX_EVENTTYPE (OMX_EVENTTYPE event);
const char* dump_OMX_INDEXTYPE (OMX_INDEXTYPE type);
void dump_OMX_PARAM_PORTDEFINITIONTYPE (OMX_PARAM_PORTDEFINITIONTYPE* port);
void dump_OMX_IMAGE_PARAM_PORTFORMATTYPE (OMX_IMAGE_PARAM_PORTFORMATTYPE* port);
void dump_OMX_BUFFERHEADERTYPE (OMX_BUFFERHEADERTYPE* header);

#endif