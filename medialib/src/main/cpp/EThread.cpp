//
// Created by eyey on 2018/11/29.
//

#include "EThread.h"
#include <thread>
#include "ELog.h"

using namespace std;

void EThread::start() {
    isExit = false;
    thread th(&EThread::threadMain, this);
    th.detach();
}

void EThread::interrupt() {
    ELOGInfo("send thread interrupt signal");
    isExit = true;
    for (int i = 0; i < 200; i++) {
        if (isRunning) {
            ESleep(1);
            continue;
        } else {
            ELOGInfo("thread interrupt");
            return;
        }
    }
    ELOGInfo("thread interrupt timeout");


}

void EThread::threadMain() {
    isRunning = true;
    ELOGInfo("thread enter,pid=%d",this_thread::get_id().id());
    main();
    ELOGInfo("thread exit,pid=%d",this_thread::get_id().id());
    isRunning = false;
}

void ESleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}
