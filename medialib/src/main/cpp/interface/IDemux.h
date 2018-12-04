//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_EDEMUX_H
#define MEDIADEMO_EDEMUX_H


#include "../XData.h"
#include "../EThread.h"
#include "../DecoderParameter.h"

class IDemux : public EThread {
public:
    virtual bool open(const char *url) =0;

    virtual XData read() = 0;

    virtual DecoderParameter findVParameter() = 0;

    virtual void main();
};


#endif //MEDIADEMO_EDEMUX_H