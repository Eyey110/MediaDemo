#include <jni.h>
#include <string>
#include <android/log.h>


#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,"zhengliao",__VA_ARGS__)

extern "C" {
#include <libavcodec/avcodec.h>
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_eyey_medialib_NativeTest_stringFromJNI(JNIEnv *env, jclass type) {

    std::string hello = "Hello from C++";
    hello += avcodec_configuration();
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_eyey_medialib_NativeTest_open(JNIEnv *env, jclass type, jstring url_, jobject handle) {
    const char *url = env->GetStringUTFChars(url_, 0);

    jboolean result = 0;
    FILE *fp = fopen(url, "rb");
    if (!fp) {
        LOGW("%s open failed",url);
    } else {
        LOGW("%s open success",url);
        fclose(fp);
        result = 1;
    }

    env->ReleaseStringUTFChars(url_, url);
    return result;
}