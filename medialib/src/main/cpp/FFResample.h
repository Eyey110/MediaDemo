//
// Created by Eyey on 2019/4/26.
//

#ifndef MEDIADEMO_FFRESAMPLE_H
#define MEDIADEMO_FFRESAMPLE_H


#include "interface/IResample.h"
struct SwrContext;
class FFResample : IResample{
public:
    virtual bool open(DecoderParameter in,DecoderParameter out=DecoderParameter());
    virtual XData resample(XData indata);

protected:
protected:
    SwrContext *actx = 0;
};


#endif //MEDIADEMO_FFRESAMPLE_H
