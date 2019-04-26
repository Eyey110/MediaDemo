//
// Created by Eyey on 2019/4/9.
//

#include "XEGL.h"
#include <EGL/egl.h>
#include <android/native_window_jni.h>
#include "ELog.h"

class CXEGL : public XEGL {


public:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLSurface surface = EGL_NO_SURFACE;
    EGLContext context = EGL_NO_CONTEXT;

    void draw() {
        if (display != EGL_NO_DISPLAY && surface != EGL_NO_SURFACE) {
            eglSwapBuffers(display, surface);
        }
    }

    bool init(void *window) {
        ANativeWindow *nwin = static_cast<ANativeWindow *>(window);
        //获取显示窗口
        display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        if (display == EGL_NO_DISPLAY) {
            ELOGInfo("get display error");
            return false;
        }
        ELOGInfo("get display success");
        //初始化display
        if (EGL_TRUE != eglInitialize(display, 0, 0)) {
            ELOGInfo("get display error");
            return false;
        }
        EGLint attr[] = {
                EGL_RED_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_BLUE_SIZE, 8,
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_NONE
        };
        //创建surface
        EGLConfig eglConfig = 0;
        EGLint configNum = 0;
        if (EGL_TRUE != eglChooseConfig(display, attr, &eglConfig, 1, &configNum)) {
            ELOGInfo("eglChooseConfig error");
            return false;
        }
        ELOGInfo("eglChooseConfig success");
        surface = eglCreateWindowSurface(display, eglConfig, nwin, NULL);
        if (surface == EGL_NO_SURFACE) {
            ELOGError("eglCreateWindowSurface error");
            return false;
        }
        ELOGInfo("eglCreateWindowSurface success");

        //创建EGL上下文
        EGLint contextAttr[] = {
                EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
        };
        context = eglCreateContext(display, eglConfig, EGL_NO_CONTEXT, contextAttr);
        if (context == EGL_NO_CONTEXT) {
            ELOGInfo("eglCreateContext error");
            return false;
        }
        ELOGInfo("eglCreateContext success");

        if (EGL_TRUE != eglMakeCurrent(display, surface, surface, context)) {
            ELOGInfo("eglMakeCurrent error");
            return false;
        }
        ELOGInfo("eglMakeCurrent success");
        return true;
    }
};

XEGL *XEGL::get() {
    static CXEGL xegl;
    return &xegl;
}
