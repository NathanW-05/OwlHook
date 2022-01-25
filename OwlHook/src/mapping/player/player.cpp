#include "player.h"
#include "../../jni/jni_handler.h"
#include <iostream>

player::player(jobject obj)
{
	m_player = obj;
}

float player::get_health()
{
	jmethodID get_health = jni::env->GetMethodID(jni::env->GetObjectClass(m_player), ("bn"), ("()F"));
	return jni::env->CallFloatMethod(m_player, get_health);
}

void player::set_health(float health)
{
	jmethodID get_health = jni::env->GetMethodID(jni::env->GetObjectClass(m_player), ("i"), ("(F)V"));
	return jni::env->CallVoidMethod(m_player, get_health, health);
}