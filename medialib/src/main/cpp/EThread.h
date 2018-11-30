//
// Created by eyey on 2018/11/29.
//

#ifndef MEDIADEMO_ETHREAD_H
#define MEDIADEMO_ETHREAD_H


void ESleep(int mis);

class EThread {
public:
    virtual void start();

    virtual void interrupt();


    virtual void main() {}

protected:
    bool isExit = false;
    bool isRunning = false;

    void threadMain();

};

#endif //MEDIADEMO_ETHREAD_H
