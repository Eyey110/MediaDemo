//
// Created by eyey on 2018/11/28.
//

#include "FFDemux.h"
#include "ELog.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}


FFDemux::FFDemux() {
    if (!is_init) {
        av_register_all();
        avcodec_register_all();
        avformat_network_init();
        is_init = true;
        ELOGDebug("register ffmpeg all success!");
    }
}


bool FFDemux::open(const char *url) {
    int suc = 0;
    char errorStr[1024] = {0};
    suc = avformat_open_input(&afc, url, 0, 0);
    if (!suc) {
        av_strerror(suc, errorStr, sizeof(errorStr));
        ELOGError("open %s failed", url);
        return false;
    }
    suc = avformat_find_stream_info(afc, 0);
    if (!suc) {
        av_strerror(suc, errorStr, sizeof(errorStr));
        ELOGError("find info %s failed", url);
        return false;
    }
    ELOGDebug("open %s success", url);
    return true;
}

XData FFDemux::read() {
    AVPacket *avPacket = av_packet_alloc();
    int suc = av_read_frame(afc, avPacket);
    XData data;
    if (!suc) {
        av_packet_free(&avPacket);
        return XData();
    }
    data.data = reinterpret_cast<unsigned char *>(avPacket);
    data.size = avPacket->size;
    return data;
}