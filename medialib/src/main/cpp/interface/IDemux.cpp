//
// Created by eyey on 2018/11/28.
//

#include "IDemux.h"

void IDemux::main() {
    while (!isExit) {
        XData d = read();
        if (d.size <=0)break;
        notifyObservers(d);
    }
}
