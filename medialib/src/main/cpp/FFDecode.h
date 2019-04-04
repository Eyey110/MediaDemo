//
// Created by eyey on 2018/12/4.
//

#ifndef MEDIADEMO_FFDECODE_H
#define MEDIADEMO_FFDECODE_H


#include "interface/IDecode.h"

class FFDecode : public IDecode {

public:
    virtual bool open(DecoderParameter parameter);


    virtual bool sendPackage(XData data);

    virtual XData receiveFrame();

protected:
    AVCodecContext *context = 0;
    AVFrame *frame = 0;
};


#endif //MEDIADEMO_FFDECODE_H
