//
// Created by eyey on 2018/11/29.
//

#ifndef MEDIADEMO_ETHREAD_H
#define MEDIADEMO_ETHREAD_H

void ESleep(int mis);

class EThread {
public:
    //开启这个线程
    virtual void start();

    //尝试中断
    virtual void interrupt();

    //子类实现。执行的代码段
    virtual void main(){};

protected:
    bool isExit = false;
    bool isRunning = false;

    void threadMain();

};

#endif //MEDIADEMO_ETHREAD_H
