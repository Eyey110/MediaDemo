//
// Created by Eyey on 2019/4/9.
//

#include "XTexture.h"
#include "XShader.h"
#include "ELog.h"
#include "XEGL.h"


class CTexture : public XTexture {
public:
    XShader sh;

    virtual bool init(void *win) {
        if (!win) {
            ELOGInfo("Texture init failure,windows is null");
            return false;
        }
        if (!XEGL::get()->init(win)) {
            return false;
        }

        return sh.init();
    }

    virtual void draw(unsigned char *data[], int width, int height) {
        sh.getTexture(0, width, height, data[0]);
        sh.getTexture(1, width / 2, height / 2, data[1]);
        sh.getTexture(2, width / 2, height / 2, data[2]);
        sh.draw();
        XEGL::get()->draw();
    }
};


XTexture *XTexture::create() {
    return new CTexture();
}
