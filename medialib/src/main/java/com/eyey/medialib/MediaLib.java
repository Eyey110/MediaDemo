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


    public static native  void openAVFile(String path);
    public static native String stringFromJNI();
    public static native boolean open(String url,Object handle);
}
