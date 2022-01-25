#include "gui_ingame.h"
#include "../../jni/jni_handler.h"

jobject gui_ingame::get_chat_gui(jobject ingame_gui_instance)
{
	jmethodID get_chat_gui = jni::env->GetMethodID(jni::env->GetObjectClass(ingame_gui_instance), ("d"), ("()Lavt;"));
	return jni::env->CallObjectMethod(ingame_gui_instance, get_chat_gui);
}