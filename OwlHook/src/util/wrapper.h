#pragma once

#include <Windows.h>
#include <memory>

namespace wrapper
{
	inline void* get_module_handle(const char* name) 
	{
		auto h_module = GetModuleHandleA(name);

		return h_module;
	}

	inline HWND find_window(const char* name)
	{
		auto res = FindWindowA(nullptr, name);

		return res;
	}

	inline void* get_proc_address(const char* name, void* handle)
	{
		auto p_procedure = GetProcAddress(reinterpret_cast<HMODULE>(handle), name);

		return p_procedure;
	}

	inline RECT get_window_rect(const char* name)
	{
		RECT res;
		GetWindowRect(find_window(name), &res);

		return res;
	}

	struct c_context
	{
		HDC m_hdc_devicectx;
		HGLRC m_glrenderctx;
		HGLRC m_oglrenderctx;
	};

	inline std::shared_ptr<c_context> create_gl_context()
	{
		std::shared_ptr<c_context> res = std::make_shared<c_context>();

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,       
			32,                   
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   
			8,                    
			0,                    
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		res->m_hdc_devicectx = GetDC(find_window("Minecraft 1.8.9"));

		int pixel_format = ChoosePixelFormat(res->m_hdc_devicectx, &pfd);
		SetPixelFormat(res->m_hdc_devicectx, pixel_format, &pfd);

		res->m_oglrenderctx = wglGetCurrentContext();
		res->m_glrenderctx = wglCreateContext(res->m_hdc_devicectx);
		return res;
	}
}

