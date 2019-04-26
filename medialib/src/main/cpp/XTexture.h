//
// Created by Eyey on 2019/4/9.
//

#ifndef MEDIADEMO_XTEXTURE_H
#define MEDIADEMO_XTEXTURE_H


class XTexture {
public:
    virtual bool init(void *win) = 0;
    static XTexture *create();

    virtual void draw(unsigned char *data[],int width,int height)=0;
};


#endif //MEDIADEMO_XTEXTURE_H
