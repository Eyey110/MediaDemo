//
// Created by Eyey on 2019/4/9.
//

#ifndef MEDIADEMO_GLVIDEOVIEW_H
#define MEDIADEMO_GLVIDEOVIEW_H


#include "interface/IVideoView.h"
#include "android/native_window_jni.h"
#include "XTexture.h"

class GLVideoView : public IVideoView {

public:
    virtual void setRenderer(void *win);

    virtual void render(XData data);


protected:
    ANativeWindow *window = 0;
    XTexture *texture = 0;
};


#endif //MEDIADEMO_GLVIDEOVIEW_H
