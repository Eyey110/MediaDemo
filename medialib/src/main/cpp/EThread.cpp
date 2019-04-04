//
// Created by eyey on 2018/11/29.
//

#include "EThread.h"
#include <thread>
#include "ELog.h"
#include "unistd.h"


using namespace std;

void EThread::start() {
    isExit = false;
    thread th(&EThread::threadMain,this);
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
            ELOGInfo("thread interrupt success");
            return;
        }
    }
    ELOGInfo("thread interrupt timeout");


}

void EThread::threadMain() {
    isRunning = true;
    ELOGInfo("thread enter,tid=%d", gettid());
    main();
    ELOGInfo("thread exit,tid=%d", gettid());
    isRunning = false;
}

void ESleep(int mis) {
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}
