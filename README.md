openmax-h264
============

#### An OpenMAX IL example that records an H.264 video with a Raspberry Pi ####

The Multi-Media Abstraction Layer (MMAL) library provided by Broadcom is not documented, so it's nearly impossible to understand how to use it. Furthermore, it's a library that wraps all the OpenMAX IL specification, so if you simply need to record an H.264 video like in this example, you can just ignore that extra layer and talk directly to OpenMAX IL. Once you understand OpenMAX IL, it's affordable to try to write your own programs without MMAL. In other words, if you are new to the OpenMAX world, it's better to learn OpenMAX IL than MMAL, which is not documented and only works with Broadcom devices.

This example records a 3 second video in H.264 format. The components involved are: `camera`, `video_encode` and `null_sink`.

If you want to play the video, you'll need to wrap it with a container format (some video players couldn't require this step), e.g. Matroska. You can download Matroska tools from [here](http://www.bunkus.org/videotools/mkvtoolnix). Then, convert the H.264 file to a Matroska file:

```
$ mkvmerge --default-duration 0:25p -o video.mkv video.h264
```

Where `25p` is the encoding framerate of the h264 video. For example, if you record a 640x480 @30fps, then you should encode the matroska file with `--default-duration 0:30p`.

Where

Build steps:

- Download and install the `gcc` and `make` programs.
- Download this repository.
- Compile and execute: `make && ./h264`

Useful documentation:

- [OpenMAX IL Specification v1.1.2](https://www.khronos.org/registry/omxil/specs/OpenMAX_IL_1_1_2_Specification.pdf)
- [Understanding OpenMAX IL](http://www.slideshare.net/pchethan/understanding-open-max-il-18376762)
- [Broadcom OpenMAX IL components](https://github.com/raspberrypi/firmware/tree/master/documentation/ilcomponents)
- [OpenMAX IL header files](https://github.com/raspberrypi/firmware/tree/master/opt/vc/include/IL)