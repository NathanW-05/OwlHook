#include "../../owlhook.h"
#include "../../gui/menu/menu.h"

#include "../../gui/imgui/imgui.h"
#include "../../gui/imgui/imgui_impl_win32.h"
#include "../../gui/imgui/imgui_impl_opengl2.h"
#include "../../gui/imgui/imgui_internal.h"

#include <mutex>
#include <gl/GL.h>

#include "../../hook/MinHook.h"
#include "../../util/wrapper.h"

std::shared_ptr<wrapper::c_context> hooks::gl_context = nullptr;

std::once_flag flag;
std::once_flag flag2;

void Colors() {
	ImGuiStyle& style = ImGui::GetStyle();

	style.ScrollbarRounding = 0;
	style.WindowMinSize = ImVec2(480, 295);

	style.Colors[ImGuiCol_WindowBg] = ImColor(16, 16, 16);
	style.ItemSpacing = ImVec2{ 10.0f,10.0f };
	style.Colors[ImGuiCol_ChildBg] = ImColor(24, 24, 24);
	style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
	style.Colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);

	style.Colors[ImGuiCol_Header] = ImColor(30, 30, 30);
	style.Colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 28);
	style.Colors[ImGuiCol_HeaderHovered] = ImColor(28, 28, 28);

	style.Colors[ImGuiCol_Button] = ImColor(31, 31, 31);
	style.Colors[ImGuiCol_ButtonActive] = ImColor(34, 34, 34);
	style.Colors[ImGuiCol_ButtonHovered] = ImColor(34, 34, 34);

	style.Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 255);
}

int __stdcall hooks::swap_buffers_hk(HDC hdc) {

	static auto mc_window = wrapper::find_window("Minecraft 1.8.9");
	auto window_rect = wrapper::get_window_rect("Minecraft 1.8.9");

	std::call_once(flag, [&]() {
		gl_context = wrapper::create_gl_context();
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(mc_window);
		ImGui_ImplOpenGL2_Init();

		return hooks::oswap_buffers(hdc);
	});

	if (owlhook::unloading)
	{
		return hooks::oswap_buffers(hdc);
	}

	wglMakeCurrent(gl_context->m_hdc_devicectx, gl_context->m_glrenderctx);

	ImGuiIO& io = ImGui::GetIO();

	if (owlhook::menu_open)
	{
		Colors();

		io.MouseDrawCursor = true;
		menu::render();
		
		glViewport(0, 0, window_rect.right, window_rect.top);
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	io.MouseDrawCursor = false;

	wglMakeCurrent(gl_context->m_hdc_devicectx, gl_context->m_oglrenderctx);

	return hooks::oswap_buffers(hdc);
}
