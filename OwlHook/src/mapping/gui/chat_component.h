#pragma once

#include <jni.h>
#include "../../jni/jni_handler.h"

class chat_component
{
private:
	jobject obj;

public:
	chat_component(const char* message)
	{
		auto chat_component_class = jni::env->FindClass("eu");
		auto constructor = jni::env->GetMethodID(chat_component_class, "<init>", "(Ljava/lang/String;)V");
		obj = jni::env->NewObject(chat_component_class, constructor, message);
	}
};