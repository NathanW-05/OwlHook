#pragma once

#include <jni.h>

namespace jni
{
	inline JavaVM* jvm;
	inline JNIEnv* env;

	void attach();
}