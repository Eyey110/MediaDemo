package com.eyey.medialib;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

/**
 * 2019/4/9
 *
 * @author zhengliao
 */
public class XPlay extends GLSurfaceView implements SurfaceHolder.Callback {
    public XPlay(Context context) {
        super(context);
    }

    public XPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
//        super.surfaceCreated(holder);
        MediaLib.initWindow(holder.getSurface());

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
//        super.surfaceChanged(holder, format, w, h);
    }


    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
//        super.surfaceDestroyed(holder);
    }


}
