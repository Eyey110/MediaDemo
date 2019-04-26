//
// Created by Eyey on 2019/4/9.
//

#include "GLVideoView.h"
#include "ELog.h"

void GLVideoView::setRenderer(void *win) {
    window = static_cast<ANativeWindow *>(win);
}

void GLVideoView::render(XData data) {
    //渲染每一帧数据
    if (!window) {
        ELOGError("before render must set renderer");
        return;
    }
    if (!texture) {
        texture = XTexture::create();
        texture->init(window);
    }
    texture->draw(data.data, data.width, data.height);
}

