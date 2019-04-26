//
// Created by Eyey on 2019/4/26.
//

#include "IResample.h"

void IResample::update(XData data) {
    XData d = resample(data);
    if (d.size > 0) {
        notifyObservers(d);
    }
}
