#pragma once

#include <chrono>
#include <iostream>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

unsigned long time_since_epoch_ms()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
