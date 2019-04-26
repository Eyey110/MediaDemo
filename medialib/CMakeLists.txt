# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.




include_directories(ffmpeg/include)

set(FF_DIR ${PROJECT_SOURCE_DIR}/ffmpeg/libs/${ANDROID_ABI})

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${FF_DIR}/libavcodec.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${FF_DIR}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${FF_DIR}/libavutil.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${FF_DIR}/libswresample.so)


add_library( # Sets the name of the library.
             media-lib

             # Sets the library as a shared library.[STATIC|SHARED|MODULE]
             #SHARED:动态链接库
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/ELog.cpp
             src/main/cpp/media-lib.cpp
             src/main/cpp/FFDemux.cpp
             src/main/cpp/XData.cpp
             src/main/cpp/EThread.cpp
             src/main/cpp/DecoderParameter.cpp
             src/main/cpp/FFDecode.cpp
             src/main/cpp/FFMpegPredef.h
             src/main/cpp/GLVideoView.cpp
             src/main/cpp/XEGL.cpp
             src/main/cpp/XTexture.cpp
             src/main/cpp/XShader.cpp
             src/main/cpp/FFResample.cpp



             src/main/cpp/interface/IObserver.cpp
             src/main/cpp/interface/IDemux.cpp
             src/main/cpp/interface/IDecode.cpp
             src/main/cpp/interface/MediaType.h
             src/main/cpp/interface/IVideoView.cpp
             src/main/cpp/interface/IResample.cpp





        )





# add_library(avformat SHARED IMPORTED)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

target_link_libraries(media-lib
                        GLESv2 EGL
                        android
                        OpenSLES
                        avcodec avformat avutil swresample
                        ${log-lib})

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

