//
// Created by Eyey on 2019/4/9.
//

#ifndef MEDIADEMO_IVIDEOVIEW_H
#define MEDIADEMO_IVIDEOVIEW_H

#include "../XData.h"
#include "IObserver.h"

class IVideoView :public IObserver{
public:
    virtual void setRenderer(void *win) = 0 ;
    virtual void render(XData data) = 0;
    virtual void update(XData data);
};


#endif //MEDIADEMO_IVIDEOVIEW_H
