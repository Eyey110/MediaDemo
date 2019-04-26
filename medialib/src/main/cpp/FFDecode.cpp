//
// Created by eyey on 2018/12/4.
//

#include "FFDecode.h"
#include "ELog.h"
#include "interface/MediaType.h"

extern "C" {
#include <libavcodec/avcodec.h>
}


bool FFDecode::open(DecoderParameter parameter) {
    if (!parameter.para)return false;
    AVCodecParameters *para = parameter.para;
    //查找解码器
    AVCodec *codec = avcodec_find_decoder(para->codec_id);
    if (!codec) {
        ELOGError("find decoder failed");
        return false;
    }

    //创建解码器上下文
    context = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(context, para);
    //打开解码器
    int suc = avcodec_open2(context, 0, 0);
    if (suc!=0) {
        char buff[1024] = {0};
        av_strerror(suc, buff, sizeof(buff) - 1);
        ELOGError("%s", buff);
        return false;
    }
    if (context->codec_type == AVMEDIA_TYPE_VIDEO) {
        mediaType = MEDIA_TYPE_VIDEO;
    } else if (context->codec_type == AVMEDIA_TYPE_AUDIO) {
        mediaType = MEDIA_TYPE_AUDIO;
    } else {
        mediaType = MEDIA_TYPE_UNKNOWN;
    }
    ELOGInfo("find decoder success，type = %d", mediaType);
    return true;
}

bool FFDecode::sendPackage(XData data) {

    if (data.size <= 0 || !data.frame) {
        return false;
    }
    if (!context) {
        return false;
    }
    int re = avcodec_send_packet(context, reinterpret_cast<const AVPacket *>(data.frame));
    if (re != 0) {
        return false;
    }
    return true;
}

XData FFDecode::receiveFrame() {
    if (!context) {
        return XData();
    }
    if (!frame) {
        frame = av_frame_alloc();
    }
    int re = avcodec_receive_frame(context, frame);
    XData d;
    d.frame = (unsigned char *) frame;
    if (context->codec_type == AVMEDIA_TYPE_VIDEO) {
        d.width = frame->width;
        d.height = frame->height;
        d.size = (frame->linesize[0] + frame->linesize[1] + frame->linesize[2]) * frame->height;
    } else if (context->codec_type == AVMEDIA_TYPE_AUDIO) {
        d.size = av_get_bytes_per_sample(static_cast<AVSampleFormat>(frame->format)) *
                 frame->nb_samples * 2;
    }
    memcpy(d.data,frame->data,sizeof(d.data));
    return d;
}

