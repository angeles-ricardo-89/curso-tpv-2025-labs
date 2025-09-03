#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_suma(JNIEnv *env, jobject thiz, jint a, jint b) {
    return a + b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_sumIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                   jintArray numbers) {
    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);
    jint sum = 0;
    for (jsize i = 0; i < length; i++) {
        sum += elements[i];
    }
    env->ReleaseIntArrayElements(numbers, elements, 0);
    return sum;
}