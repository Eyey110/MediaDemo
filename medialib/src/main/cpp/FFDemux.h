//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_FFDEMUX_H
#define MEDIADEMO_FFDEMUX_H


#include "interface/IDemux.h"
#include "FFMpegPredef.h"

//准备写成一个单例，在构造函数中去注册各种解封装器，解码器
class FFDemux : public IDemux {

public:
    //打开一个av文件
    virtual bool open(const char *url);
    //读取一帧数据，后续需要送到解码器里解码，需要循环调用直到文件末尾
    virtual XData read();

    virtual DecoderParameter findVParameter();

    virtual DecoderParameter findAParameter();

    FFDemux();

private:
    static bool is_init;
    AVFormatContext *afc = 0;
    int vStreamIndex = -1;
    int aStreamIndex = -1;
};


#endif //MEDIADEMO_FFDEMUX_H
