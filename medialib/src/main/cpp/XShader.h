//
// Created by Eyey on 2019/4/9.
//

#ifndef MEDIADEMO_XSHADER_H
#define MEDIADEMO_XSHADER_H

#include <GLES2/gl2.h>

class XShader {
public:
    virtual bool init();

    virtual void getTexture(unsigned int index, int width, int height, unsigned char *buf);

    virtual void draw();

protected:
    unsigned int vsh;
    unsigned int fsh;
    unsigned int program;
    GLuint texts[100] = {0};

};


#endif //MEDIADEMO_XSHADER_H
