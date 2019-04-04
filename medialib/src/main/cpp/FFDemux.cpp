//
// Created by eyey on 2018/11/28.
//

#include "FFDemux.h"
#include "ELog.h"
#include "interface/MediaType.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/error.h>
}


bool FFDemux::is_init = false;


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
    if (suc != 0) {
        av_strerror(suc, errorStr, sizeof(errorStr));
        ELOGError("open %s failed,reason is  %s", url, errorStr);
        return false;
    }
    suc = avformat_find_stream_info(afc, 0);
    if (suc != 0) {
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
    if (suc != 0) {
        av_packet_free(&avPacket);
        return XData();
    }
    data.data = reinterpret_cast<unsigned char *>(avPacket);
    data.size = avPacket->size;
    if (avPacket->stream_index == vStreamIndex) {
        data.mediaType = MEDIA_TYPE_VIDEO;
    } else if (avPacket->stream_index == aStreamIndex) {
        data.mediaType = MEDIA_TYPE_AUDIO;
    } else {
        data.mediaType = MEDIA_TYPE_UNKNOWN;
    }
    return data;
}

DecoderParameter FFDemux::findVParameter() {
    if (!afc) {
        return DecoderParameter();
    }
    vStreamIndex = av_find_best_stream(afc, AVMEDIA_TYPE_VIDEO, -1, -1, 0, 0);
    if (vStreamIndex == AVERROR_STREAM_NOT_FOUND) {
        return DecoderParameter();
    }

    DecoderParameter parameter;
    parameter.para = afc->streams[vStreamIndex]->codecpar;
    return parameter;
}


DecoderParameter FFDemux::findAParameter() {
    if (!afc) {
        return DecoderParameter();
    }
    aStreamIndex = av_find_best_stream(afc, AVMEDIA_TYPE_AUDIO, -1, -1, 0, 0);
    if (aStreamIndex == AVERROR_STREAM_NOT_FOUND) {
        return DecoderParameter();
    }
    DecoderParameter parameter;
    parameter.para = afc->streams[aStreamIndex]->codecpar;
    return parameter;
}
