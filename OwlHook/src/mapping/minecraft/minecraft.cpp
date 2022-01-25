#include "minecraft.h"
#include "../../jni/jni_handler.h"
#include <iostream>

// getMinecraft() method
jobject minecraft::get_minecraft() 
{
	auto mc_class = jni::env->FindClass("ave");
	auto get_minecraft = jni::env->GetStaticMethodID(mc_class, "A", "()Lave;");

	jni::env->DeleteLocalRef(mc_class);

	return jni::env->CallStaticObjectMethod(mc_class, get_minecraft);
}

// getDebugFps() method
int minecraft::get_debug_fps()
{
	auto mc_class = jni::env->FindClass("ave");
	auto get_debug_fps = jni::env->GetStaticMethodID(mc_class, "ai", "()I");

	jni::env->DeleteLocalRef(mc_class);

	return jni::env->CallStaticIntMethod(mc_class, get_debug_fps);
}

// thePlayer field
player minecraft::get_local_player()
{
	auto mc_class = jni::env->FindClass("ave");
	auto player = jni::env->GetFieldID(mc_class, "h", "Lbew;");

	jni::env->DeleteLocalRef(mc_class);

	return jni::env->GetObjectField(minecraft::get_minecraft(), player);
	return nullptr;
}

// ingameGUI field
jobject minecraft::get_ingame_gui()
{
	auto mc_class = jni::env->FindClass("ave");
	auto ingame_gui = jni::env->GetFieldID(mc_class, "q", "Lavo;");

	jni::env->DeleteLocalRef(mc_class);

	return jni::env->GetObjectField(minecraft::get_minecraft(), ingame_gui);
}