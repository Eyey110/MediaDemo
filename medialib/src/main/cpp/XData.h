//
// Created by eyey on 2018/11/28.
//

#ifndef MEDIADEMO_XDATA_H
#define MEDIADEMO_XDATA_H


class XData {

public:
    unsigned char *data;
    int size;

    XData();

    void drop();

    int mediaType;
};


#endif //MEDIADEMO_XDATA_H
