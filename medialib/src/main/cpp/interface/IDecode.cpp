//
// Created by eyey on 2018/12/4.
//

#include "IDecode.h"
#include "MediaType.h"
#include "../ELog.h"

/**
 * 不停的从队列中获取数据来解码
 */
void IDecode::main() {
    while (!isExit) {
        packMutex.lock();
        if (packs.empty()) {
            packMutex.unlock();
            ESleep(1);
            continue;
        }

        XData pack = packs.front();
        packs.pop_front();
        if (this->sendPackage(pack)) {
            while (!isExit) {
                XData frame = receiveFrame();
                if (!frame.frame || frame.size == 0)break;
//                ELOGInfo("receive frame size : %d", frame.size);
                this->notifyObservers(frame);
                ESleep(1);
            }
        }
        pack.drop();
        packMutex.unlock();
        ESleep(1);
    }
}

void IDecode::update(XData data) {
    if (mediaType != data.mediaType) {
        return;
    }
    while (!isExit) {
        packMutex.lock();
        if (packs.size() < maxBuffer) {
            packs.push_back(data);
            packMutex.unlock();
            break;
        }
        packMutex.unlock();
        ESleep(1);
    }

}

