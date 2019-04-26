//
// Created by Eyey on 2019/4/9.
//

#ifndef MEDIADEMO_XEGL_H
#define MEDIADEMO_XEGL_H


class XEGL {
public:
    virtual bool init(void *window) = 0;
    virtual void draw()=0;

    static XEGL *get();
};


#endif //MEDIADEMO_XEGL_H
