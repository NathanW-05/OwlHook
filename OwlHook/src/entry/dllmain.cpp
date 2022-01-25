#include <Windows.h>
#include "../owlhook.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    { // this is the main entry point for our cheat
        owlhook::h_module = hModule;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)owlhook::main_loop, nullptr, 0, nullptr);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

