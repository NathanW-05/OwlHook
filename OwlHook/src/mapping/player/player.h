#pragma once

#include <jni.h>

class player {

private:
	jobject m_player;
public:
	player(jobject obj);

	float get_health();
	void set_health(float health);

	const jobject get_origin_object()
	{
		return m_player;
	}
};