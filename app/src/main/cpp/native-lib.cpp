#include <string.h>
#include <jni.h>
#include <assert.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include <malloc.h>


extern "C" void JNIEXPORT
Java_org_nunocky_readassetfromjni_MainActivity_hello(JNIEnv *env, jobject thiz,
                                                     jobject assetManager) {
    AAssetManager *mgr = AAssetManager_fromJava(env, assetManager);

    AAsset *testAsset = AAssetManager_open(mgr, "test.txt", AASSET_MODE_UNKNOWN);

    if (testAsset) {
        size_t assetLength = AAsset_getLength(testAsset);

        __android_log_print(ANDROID_LOG_DEBUG, "Native", "Asset file size: %d\n", assetLength);

        char *buffer = (char *) malloc(assetLength + 1);

        AAsset_read(testAsset, buffer, assetLength);

        buffer[assetLength] = 0;

        __android_log_print(ANDROID_LOG_INFO, "Native", "%s", buffer);

        free(buffer);

        AAsset_close(testAsset);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, "Native", "Cannot open file");
    }
}
