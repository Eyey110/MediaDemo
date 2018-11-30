//
// Created by eyey on 2018/11/29.
//

#ifndef MEDIADEMO_ELOG_H
#define MEDIADEMO_ELOG_H

#include <libavcodec/avcodec.h>

#define __ETAG "Eyey"

#ifdef ANDROID

#include <android/log.h>

#define ELOGDebug(format, ...) __android_log_print(ANDROID_LOG_DEBUG,__ETAG,format,##__VA_ARGS__)
#define ELOGError(format, ...) __android_log_print(ANDROID_LOG_ERROR,__ETAG,format,##__VA_ARGS__)
#define ELOGInfo(format, ...) __android_log_print(ANDROID_LOG_INFO,__ETAG,format,##__VA_ARGS__)

#else
#define MMKVError(format, ...)                                                                     \
    {}
#define MMKVWarning(format, ...)                                                                   \
    {}
#define MMKVInfo(format, ...)                                                                      \
    {}
#define MMKVDebug(format, ...)                                                                     \
    {}
#endif //ANDROID

#endif //MEDIADEMO_ELOG_H


static int ffmpeg_lockmgr_callback(void **mutex, AVLockOp op);