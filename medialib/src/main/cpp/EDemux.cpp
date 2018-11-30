//
// Created by eyey on 2018/11/28.
//

#include "EDemux.h"

void EDemux::main() {
    while (!isExit) {
        XData d = read();
        if (d.size <= 0)break;
    }
}
