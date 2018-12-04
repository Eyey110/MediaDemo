package com.eyey.medialib;

/**
 * Created on 2018/11/14.
 *
 * @author zhengliao
 */
public class MediaLib {
    static {
        System.loadLibrary("media-lib");
    }
    public static native boolean open(String url,Object handle);
}
