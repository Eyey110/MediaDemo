//
// Created by eyey on 2018/11/14.
//

#include <jni.h>
#include <string>
#include "ELog.h"


extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
}


static double r2d(AVRational rational) {
    return rational.num == 0 || rational.den == 0 ? 0 : ((double) rational.num) /
                                                        ((double) rational.den);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_eyey_medialib_MediaLib_openAVFile(JNIEnv *env, jclass type, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);
    AVFormatContext *context = nullptr;
    int re = avformat_open_input(&context, path, 0, 0);
    if (re != 0) {
        ELOGDebug("avformat open failed : %s", av_err2str(re));

    }
    ELOGDebug("avformat open success : %s", path);
    re = avformat_find_stream_info(context, 0);
    if (re != 0) {
        ELOGDebug("avformat find stream info failed");
    }
    ELOGDebug("duration = %lld , nb_streams = %d", context->duration, context->nb_streams);
    for (int i = 0; i < context->nb_streams; i++) {
        AVStream *as = context->streams[i];
        if (as->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            //视频

        } else if (as->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            //音频
        }
    }
    ELOGDebug("test");
    avformat_close_input(&context);
    env->ReleaseStringUTFChars(path_, path);
}


jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    av_register_all();
    avformat_network_init();
    return JNI_VERSION_1_6;//必须返回这个值
}


extern "C"
JNIEXPORT jstring JNICALL
Java_com_eyey_medialib_MediaLib_stringFromJNI(JNIEnv *env, jclass type) {

    std::string hello = "Hello from C++";
    hello += avcodec_configuration();

    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_eyey_medialib_MediaLib_open(JNIEnv *env, jclass type, jstring url_, jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);

    jboolean result = 0;
    FILE *fp = fopen(url, "rb");
    if (!fp) {
        ELOGDebug("File %s open failed", url);
    } else {
        ELOGDebug("File %s open success", url);
        fclose(fp);
        result = 1;
    }

    env->ReleaseStringUTFChars(url_, url);
    return result;
}