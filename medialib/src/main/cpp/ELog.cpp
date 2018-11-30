//
// Created by eyey on 2018/11/29.
//
#include "ELog.h"


int ffmpeg_lockmgr_callback(void **mutex, AVLockOp op) {
    switch (op){
        case AV_LOCK_CREATE:///< Create a mutex
            break;
        case AV_LOCK_OBTAIN:///< Create a mutex
            break;
        case AV_LOCK_RELEASE:///< Create a mutex
            break;
        case AV_LOCK_DESTROY:
            break;///< Create a mutex
    }
    return 0;
}
