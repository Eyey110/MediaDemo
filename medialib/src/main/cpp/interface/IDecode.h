//
// Created by eyey on 2018/12/4.
//

#ifndef MEDIADEMO_IDECODE_H
#define MEDIADEMO_IDECODE_H


#include <list>
#include "../DecoderParameter.h"
#include "IObserver.h"

class IDecode :public IObserver{
public:
    //打开解码器，根据不同的解码器具体实现
    virtual bool open(DecoderParameter parameter) = 0;


    virtual bool sendPackage(XData data) = 0;

    virtual XData receiveFrame() = 0;

    virtual void update(XData data);

    int mediaType;

    int maxBuffer = 100;

protected:
    virtual void main();

    std::list<XData> packs;

    std::mutex packMutex;
};


#endif //MEDIADEMO_IDECODE_H
