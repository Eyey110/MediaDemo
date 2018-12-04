//
// Created by eyey on 2018/11/14.
//

#include <jni.h>
#include <string>
#include "ELog.h"
#include "FFDemux.h"
#include "interface/IDemux.h"
#include "EThread.h"



extern "C"
JNIEXPORT jboolean JNICALL
Java_com_eyey_medialib_MediaLib_open(JNIEnv *env, jclass type, jstring url_, jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);
    jboolean result = 0;
    IDemux *demux = new FFDemux;
    demux->open(url);
    demux->start();
    ESleep(300);
    demux->interrupt();
    env->ReleaseStringUTFChars(url_, url);
    return result;
}