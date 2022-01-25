#include "console.h"
#include <Windows.h>

void create_console()
{
	FILE* fStdIn, * fStdOut, * fStdErr;

	AllocConsole();
	SetConsoleTitleA("owlhook Console");

	fStdIn = freopen("conin$", "r", stdin);
	fStdOut = freopen("conout$", "w", stdout);
	fStdErr = freopen("conout$", "w", stderr);
}