#include "jni_handler.h"
#include <iostream>

// attach to the jvm inside of minecraft's memory space
void jni::attach()
{
	jsize count;
	if (JNI_GetCreatedJavaVMs(&jvm, 1, &count) != JNI_OK || count == 0) {
		return;
	}
	jint res = jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
	if (res == JNI_EDETACHED)
		res = jvm->AttachCurrentThread((void**)&env, nullptr);
	if (res != JNI_OK) {
		return;
	}
}