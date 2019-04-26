//
// Created by Eyey on 2019/4/26.
//

#ifndef MEDIADEMO_IRESAMPLE_H
#define MEDIADEMO_IRESAMPLE_H

#include "../DecoderParameter.h"
#include "IObserver.h"

class IResample : public IObserver{
public:
    virtual bool open(DecoderParameter in,DecoderParameter out=DecoderParameter()) = 0;
    virtual XData resample(XData indata) = 0;
    virtual void update(XData data);
    int outChannels = 2;
    int outFormat = 1;
};


#endif //MEDIADEMO_IRESAMPLE_H
