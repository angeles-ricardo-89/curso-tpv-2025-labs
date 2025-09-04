#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_stringFromJNI(
        JNIEnv *env,
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
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Mult %d * %d", a, b);
    return a * b;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_multiplyIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                        jintArray numbers) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Multiply Integer Array List");

    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);
    jint product = 1;
    for (jsize i = 0; i < length; i++) {
        product *= elements[i];
    }

    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Multiply result: %d", product);

    env->ReleaseIntArrayElements(numbers, elements, 0);
    return product;
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_divide(JNIEnv *env, jobject thiz, jint a, jint b) {
    if (b == 0) {
        __android_log_print(ANDROID_LOG_ERROR, "NATIVE_LIB", "Se divide por 0 !");
        return 0;
    }
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Div %d / %d", a, b);
    return a / b;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_priv_tpvsolutions_ndklab_MainActivity_divideIntegerArrayList(JNIEnv *env, jobject thiz,
                                                                      jintArray numbers) {
    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Divide Integer Array List");
    jint *elements = env->GetIntArrayElements(numbers, nullptr);
    jsize length = env->GetArrayLength(numbers);

    if (length == 0) {
        __android_log_print(ANDROID_LOG_WARN, "NATIVE_LIB", "Array vacío, retornando 0");
        return 0;
    }

    jint result = elements[0];

    for (jsize i = 1; i < length; i++) {
        if (elements[i] == 0) {
            __android_log_print(ANDROID_LOG_ERROR, "NATIVE_LIB", "Division by zero at index %d", i);
            env->ReleaseIntArrayElements(numbers, elements, JNI_ABORT);
            return 0;
        }
        result /= elements[i];
    }

    __android_log_print(ANDROID_LOG_DEBUG, "NATIVE_LIB", "Divide result: %d", result);

    env->ReleaseIntArrayElements(numbers, elements, JNI_ABORT);
    return result;
}