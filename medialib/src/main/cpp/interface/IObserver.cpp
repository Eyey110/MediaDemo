//
// Created by eyey on 2018/11/30.
//

#include "IObserver.h"

void IObserver::addObserver(IObserver *observer) {
    if (!observer)return;
    m_lock.lock();
    obsList.push_back(observer);
    m_lock.unlock();
}

void IObserver::notifyObservers(XData data) {
    m_lock.lock();
    int size = obsList.size();
    for (int i = 0; i < size; i++) {
        obsList[i]->update(data);
    }
    m_lock.unlock();
}




