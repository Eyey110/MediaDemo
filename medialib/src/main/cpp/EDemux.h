//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_EDEMUX_H
#define MEDIADEMO_EDEMUX_H


#include "XData.h"
#include "FFMpegPredef.h"
#include "EThread.h"

class EDemux : EThread {

    virtual bool open(const char *url) =0;

    virtual XData read() = 0;


protected:
    virtual void main();

    EDemux();

};


#endif //MEDIADEMO_EDEMUX_H
