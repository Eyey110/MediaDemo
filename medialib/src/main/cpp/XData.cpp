//
// Created by eyey on 2018/11/28.
//

#include "XData.h"

extern "C" {
#include <libavformat/avformat.h>
}

XData::XData() {
    this->frame = 0;
    this->size = 0;
}

void XData::drop() {
    if (!data) return;
    if (type == AVPACKET_TYPE) {
        av_packet_free((AVPacket **) &frame);
    } else {
        delete data;
    }
    frame = 0;
    size = 0;

}

bool XData::alloc(int size, const char *data) {
    drop();
    type = UCHAR_TYPE;
    if (size > 0) {
        this->frame = new unsigned char[size];
    }
    if(!this->frame){
        return false;
    }
    if(data){
        memcpy(this->frame,data,size);
    }
    return true;
}
