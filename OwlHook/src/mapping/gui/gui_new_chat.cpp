#include "gui_new_chat.h"
#include "../../jni/jni_handler.h"
#include "chat_component.h"
#include <iostream>

void gui_new_chat::print_clientside_message(const char* chat_message, jobject gui_new_chat_instance)
{
	// For some reason this doesn't work, I know it must be an issue with passing in the message which is strange because alone everything
	// checks out just fine: weird.

	/* 
	chat_component* message = new chat_component(chat_message);

	jmethodID print_chat_message = jni::env->GetMethodID(jni::env->GetObjectClass(gui_new_chat_instance), ("a"), ("(Leu;)V"));

	std::cout << print_chat_message << std::endl;
	std::cout << message << std::endl;

	return jni::env->CallVoidMethod(gui_new_chat_instance, print_chat_message, nullptr);
	*/
}