//
// Created by eyey on 2018/11/28.
//

#include "XData.h"
extern "C" {
#include <libavformat/avformat.h>
}

XData::XData() {
    this->data = 0;
    this->size = 0;
}

void XData::drop() {
    av_packet_free((AVPacket **) (&this->data));

}
