//
// Created by eyey on 2018/12/4.
//

#include "FFDecode.h"

extern "C" {
#include <libavcodec/avcodec.h>
}


bool FFDecode::open(DecoderParameter parameter) {
    if (!parameter.para)return false;
    AVCodecParameters *para = parameter.para;
    //查找解码器
    AVCodec *codec = avcodec_find_decoder(para->codec_id);
    if (!codec) {
        return false;
    }
    //创建解码器上下文
    context = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(context, para);
    //打开解码器
    int suc = avcodec_open2(context, 0, 0);
    if (!suc) {
        return false;
    }


    return true;
}
