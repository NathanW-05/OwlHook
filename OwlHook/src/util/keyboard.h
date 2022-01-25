#pragma once

#include <Windows.h>

inline bool is_key_pressed(DWORD key)
{
	if (GetKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}