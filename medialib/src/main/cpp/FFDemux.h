//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_FFDEMUX_H
#define MEDIADEMO_FFDEMUX_H


#include "EDemux.h"

class FFDemux : public EDemux {


    virtual bool open(const char *url);

    virtual XData read();

    FFDemux();

private:
    static bool is_init = true;
    AVFormatContext *afc = 0;


};



#endif //MEDIADEMO_FFDEMUX_H
