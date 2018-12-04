//
// Created by eyey on 2018/12/4.
//

#ifndef MEDIADEMO_IDECODE_H
#define MEDIADEMO_IDECODE_H


#include "../DecoderParameter.h"
#include "IObserver.h"

class IDecode :public IObserver{
public:
    //打开解码器，根据不同的解码器具体实现
    virtual bool open(DecoderParameter parameter) = 0;

};


#endif //MEDIADEMO_IDECODE_H
