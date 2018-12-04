//
// Created by eyey on 2018/11/30.
//

#ifndef MEDIADEMO_IOBSERVER_H
#define MEDIADEMO_IOBSERVER_H


#include "../XData.h"
#include <vector>
#include <mutex>

class IObserver {
public:
    virtual void update(XData data) {
    }

    virtual void addObsever(IObserver *observer);


    virtual void notifyObservers(XData data);

private:
    std::vector<IObserver *> obsList;
    std::mutex m_lock;
};


#endif //MEDIADEMO_IOBSERVER_H
