//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_XDATA_H
#define MEDIADEMO_XDATA_H

enum DataType {
    AVPACKET_TYPE = 0,
    UCHAR_TYPE
};

class XData {

public:
    unsigned char *frame;
    unsigned char *data[8];
    int size;

    int type;

    XData();

    void drop();

    bool alloc(int size, const char *data = 0);


    int mediaType;

    int width;
    int height;
};


#endif //MEDIADEMO_XDATA_H
