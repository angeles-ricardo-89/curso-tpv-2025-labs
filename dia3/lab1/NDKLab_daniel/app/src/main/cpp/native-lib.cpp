#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Hello from C++");
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_suma(JNIEnv *env, jobject thiz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Sum %d + %d", a, b);
    return a + b;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_sumIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                   jintArray numbers) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Sum Integer Array List");
    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);
    jint sum = 0;
    for (jsize i = 0; i < length; i++) {
        sum += elements[i];
    }
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Sum result: %d", sum);
    env->ReleaseIntArrayElements(numbers, elements, 0);
    return sum;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_multiply(JNIEnv *env, jobject thiz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Mult %d + %d", a, b);
    return a * b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_divid(JNIEnv *env, jobject thiz, jint a, jint b) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Div %d + %d", a, b);
    return a / b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_multIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                    jintArray numbers) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Mult Integer Array List");
    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);
    jint mult = 1;
    for (jsize i = 0; i < length; i++) {
        mult *= elements[i];
    }
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Mult result: %d", mult);
    env->ReleaseIntArrayElements(numbers, elements, 0);
    return mult;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_divIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                   jintArray numbers) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Div Integer Array List");
    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);
    jint div = 1;
    for (jsize i = 0; i < length; i++) {
        div /= elements[i];
    }
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Div result: %d", div);
    env->ReleaseIntArrayElements(numbers, elements, 0);
    return div;
}