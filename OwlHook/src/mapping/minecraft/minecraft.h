#pragma once

#include <jni.h>
#include "../player/player.h"

namespace minecraft
{
	jobject get_minecraft();

	jobject get_ingame_gui();

	player get_local_player();

	int get_debug_fps();

}
