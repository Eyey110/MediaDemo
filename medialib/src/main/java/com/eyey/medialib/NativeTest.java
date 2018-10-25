package com.eyey.medialib;

/**
 * Created on 2018/10/24.
 *
 * @author zhengliao
 */
public class NativeTest {
    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();
    public static native boolean open(String url,Object handle);
}
