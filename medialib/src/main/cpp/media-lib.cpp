//
// Created by eyey on 2018/11/14.
//

#include <jni.h>
#include <string>
#include "ELog.h"
#include "FFDemux.h"
#include "interface/IDemux.h"
#include "EThread.h"
#include "FFDecode.h"
#include "interface/MediaType.h"
#include <android/native_window_jni.h>
#include "XEGL.h"
#include "XShader.h"
#include "interface/IVideoView.h"
#include "GLVideoView.h"


IVideoView *view = NULL;
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_eyey_medialib_MediaLib_open(JNIEnv *env, jclass type, jstring url_, jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);
    jboolean result = 0;
    IDemux *demux = new FFDemux();
    demux->open(url);


    IDecode *avdecode = new FFDecode();
    avdecode->open(demux->findVParameter());

//    IDecode *audecode = new FFDecode();
//    audecode->open(demux->findAParameter());


    demux->addObserver(avdecode);
//    demux->addObserver(audecode);
    if (view==NULL) {
        view = new GLVideoView();
    }
    avdecode->addObserver(view);

    demux->start();
    avdecode->start();
//    audecode->start();
    env->ReleaseStringUTFChars(url_, url);

    return result;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_eyey_medialib_MediaLib_initWindow(JNIEnv *env, jclass type, jobject surface) {

    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    if (view == NULL) {
        view = new GLVideoView();
    }
    view->setRenderer(window);

}