#include <jni.h>
#include <string>

 //#include <../cpp/include/opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_android_lovedj_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}



/**
 * CMake常用语法
 *https://www.jianshu.com/p/8909efe13308
 *
include_directories 函数设置了include文件夹的路径
add_library 函数设置库名和类型，其中libopencv_java3 是用户自定义的变量名，前后保持一致即可，SHARE 表示引入的库是动态链接库
set_target_properties 设置了OpenCV的动态链接库的路径
target_link_libraries 具有依赖关系的动态库链接到指定目标上，链接顺序需符合gcc链接规则，这里我们把libopencv_java3和log链接到了native-lib上。
 * */extern "C"
 JNIEXPORT jintArray JNICALL
 Java_com_android_lovedj_MainActivity_Bitmap2Grey(JNIEnv *env, jobject instance, jintArray buf,
                                                  jint w, jint h) {
     jint *cbuf;
     jboolean ptfalse = false;
     cbuf = env->GetIntArrayElements(buf, &ptfalse);
     if(cbuf == NULL){
         return 0;
     }

     Mat imgData(h, w, CV_8UC4, (unsigned char*)cbuf);
     // 注意，Android的Bitmap是ARGB四通道,而不是RGB三通道
     cvtColor(imgData,imgData,CV_BGRA2GRAY);
     cvtColor(imgData,imgData,CV_GRAY2BGRA);

     int size=w * h;
     jintArray result = env->NewIntArray(size);
     env->SetIntArrayRegion(result, 0, size, (jint*)imgData.data);
     env->ReleaseIntArrayElements(buf, cbuf, 0);
     return result;
 }