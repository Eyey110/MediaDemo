//
// Created by eyey on 2018/12/4.
//

#ifndef MEDIADEMO_FFDECODE_H
#define MEDIADEMO_FFDECODE_H


#include "interface/IDecode.h"

class FFDecode : public IDecode {

public:
    virtual bool open(DecoderParameter parameter);


protected:
    AVCodecContext *context;
};


#endif //MEDIADEMO_FFDECODE_H
