#pragma once

#include <Windows.h>

#include "util/wrapper.h"

namespace owlhook
{
	inline HMODULE h_module;

	inline bool start_unload = false;
	inline bool menu_open = true;
	inline bool unloading = false;

	void initialize();
	void main_loop();
	void unload_library();
	void hook();
}

namespace hooks 
{
	using swap_buffers_fn = int(__stdcall*)(HDC);

	inline swap_buffers_fn oswap_buffers = nullptr;

	extern std::shared_ptr<wrapper::c_context> gl_context;

	int __stdcall swap_buffers_hk(HDC);

	inline WNDPROC original_wndproc = nullptr;

	long __stdcall wndproc_hk(const HWND hwnd, unsigned int usermsg, uintptr_t wparam, long lparam);
}
   