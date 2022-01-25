#pragma once

#include <jni.h>

namespace gui_new_chat
{
	void print_clientside_message(const char* chat_message, jobject gui_new_chat_instance);
}