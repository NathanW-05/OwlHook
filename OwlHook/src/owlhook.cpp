#include "owlhook.h"
#include "util/keyboard.h"
#include "jni/jni_handler.h"
#include "mapping/mappings.h"
#include "console/console.h"
#include "util/time.h"

#include <iostream>
#include <thread>

#include "hook/MinHook.h"

#include "gui/imgui/imgui.h"
#include "gui/imgui/imgui_impl_win32.h"
#include "gui/imgui/imgui_impl_opengl2.h"
#include "gui/imgui/imgui_internal.h"

#include "util/wrapper.h"

#include "config/config.h"

bool unloaded = false;

/* cheat setup */
void owlhook::initialize()
{
	//create_console(); // init the external console, only for debug purposes
	jni::attach(); // attach to the jvm to access minecraft's heap

	std::cout << "Initialization complete and successful!" << std::endl;
}

/* calling this method self-destroys the cheat, it cannot be recovered so you must re-inject */
void owlhook::unload_library()
{
	owlhook::menu_open = false;
	Sleep(50);

	ImGui_ImplOpenGL2_Shutdown();
	wglDeleteContext(hooks::gl_context->m_glrenderctx);
	ImGui::DestroyContext();
	ImGui_ImplWin32_Shutdown();

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	SetWindowLongPtrA(wrapper::find_window("Minecraft 1.8.9"), GWLP_WNDPROC, (LONG_PTR)hooks::original_wndproc);

	hooks::gl_context = nullptr;

	unloaded = true;

	std::cout << std::endl << "Unloading owlhook... please wait for all threads to finish.";
	Sleep(1000);

	std::cout << std::endl << "Unloaded successfully! You may close this window.";

	FreeConsole();
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);

	FreeLibraryAndExitThread(owlhook::h_module, 0); // no going back beyond this point...
}

void owlhook::hook()
{
	MH_Initialize();

	auto swap_buffers_ptr = wrapper::get_proc_address("SwapBuffers", wrapper::get_module_handle("Gdi32.dll"));

	MH_CreateHook(swap_buffers_ptr, hooks::swap_buffers_hk, reinterpret_cast<void**>(&hooks::oswap_buffers));
	MH_EnableHook(MH_ALL_HOOKS);

	hooks::original_wndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrA(wrapper::find_window("Minecraft 1.8.9"), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(hooks::wndproc_hk)));
}

/* the main thread loop: everything happens here */
void owlhook::main_loop()
{
	owlhook::initialize();
	owlhook::hook();

	config::register_items();
	config::load();

	long saved_time = time_since_epoch_ms();

	while (true)
	{
		// this is our variation of client tick, using the unix epoch as a metric it runs code every 50ms
		if (time_since_epoch_ms() - saved_time > 50)
		{
			saved_time = time_since_epoch_ms();
		}

		if (owlhook::start_unload)
		{
			// unload the cheat if the delete key is pressed;
			owlhook::unloading = true;
			owlhook::unload_library();
		}
	}
}

