//
// Created by Eyey on 2019/4/26.
//
extern "C"
{
#include <libswresample/swresample.h>
}

#include "FFResample.h"
#include <libavcodec/avcodec.h>
#include "FFResample.h"
#include "ELog.h"

bool FFResample::open(DecoderParameter in, DecoderParameter out) {
    //音频重采样上下文初始化
    actx = swr_alloc();
    actx = swr_alloc_set_opts(actx,
                              av_get_default_channel_layout(2),
                              AV_SAMPLE_FMT_S16,in.para->sample_rate,
                              av_get_default_channel_layout(in.para->channels),
                              (AVSampleFormat)in.para->format,in.para->sample_rate,
                              0,0 );

    int re = swr_init(actx);
    if(re != 0) {
        ELOGError("swr_init failed!");
        return false;
    } else {
        ELOGInfo("swr_init success!");
    }
    outChannels = in.para->channels;
    outFormat = AV_SAMPLE_FMT_S16;
    return true;
}

XData FFResample::resample(XData indata) {
    if(indata.size<=0 || !indata.frame) return XData();
    if(!actx)
        return XData();
    AVFrame *frame = (AVFrame *)indata.frame;
    //输出空间的分配
    XData out;
    //通道数 * 单通道样本数 * 样本字节数
    int outsize = outChannels * frame->nb_samples * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    if(outsize <=0)return XData();
    out.alloc(outsize);
    uint8_t *outArr[2] = {0};
    outArr[0] = out.frame;
    int len = swr_convert(actx,outArr,frame->nb_samples,(const uint8_t **)frame->data,frame->nb_samples);
    if(len<=0)
    {
        out.drop();
        return XData();
    }
    ELOGInfo("swr_convert success = %d",len);
    return out;
}
