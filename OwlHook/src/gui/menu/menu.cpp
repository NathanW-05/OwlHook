#include "menu.h"

#include "../../owlhook.h"
#include "../../config/config.h"

#include "../../gui/imgui/imgui.h"
#include "../../gui/imgui/imgui_impl_opengl2.h"
#include "../../gui/imgui/imgui_impl_win32.h"
#include "../../gui/imgui/imgui_internal.h"

#include "../../gui/menu/font.h"

#include "image.h"

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include <mutex>

GLuint mouse_texture;
GLuint player_texture;
GLuint visuals_texture;
GLuint aim_texture;
GLuint setting_texture;

int texture_width = 20;
int texture_height = 20;

void load_textures()
{
	bool ret = false;

	ret = load_texture_from_memory(mouse_icon, mouse_icon_len, &mouse_texture, &texture_width, &texture_height);
	ret = load_texture_from_memory(player_icon, player_icon_len, &player_texture, &texture_width, &texture_height);
	ret = load_texture_from_memory(visuals_icon, visuals_icon_len, &visuals_texture, &texture_width, &texture_height);
	ret = load_texture_from_memory(aim_icon, aim_icon_len, &aim_texture, &texture_width, &texture_height);
	ret = load_texture_from_memory(settings_icon, settings_icon_len, &setting_texture, &texture_width, &texture_height);
}

void color_picker(const char* name, float* source, int color_id)
{
	ImGui::Dummy(ImVec2{ 40.f, 0.f });
	ImGui::SameLine();
	ImGui::Text(name);
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - 20);
	ImGui::PushID(color_id);
	ImGui::ColorEdit4(std::string{ "##" }.append("").append("Picker").c_str(), source, true | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
	ImGui::PopID();
}

void color_picker_checkbox(const char* name, float* csource, bool* bsource, int color_id, int cbox_id)
{
	ImGui::PushID(cbox_id);
	ImGui::Checkbox("", bsource);
	ImGui::PopID();
	ImGui::SameLine();
	ImGui::Dummy(ImVec2{ 5.f, 0.f });
	ImGui::SameLine();
	ImGui::Text(name);
	ImGui::SameLine(ImGui::GetContentRegionAvail().x - 20);
	ImGui::PushID(color_id);
	ImGui::ColorEdit4(std::string{ "##" }.append("").append("Picker").c_str(), csource, true | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
	ImGui::PopID();
}

void button(const char* name, void* function, int button_id)
{
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
	//ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 37.5);
	//ImGui::SameLine();
	ImGui::Dummy(ImVec2 { 40.f , 5.f});
	ImGui::SameLine();
	ImGui::PushID(button_id);
	if (ImGui::Button(name, ImVec2(ImGui::GetContentRegionAvail().x - 230, 29))) 
	{
		((void (*)(void)) function)();
	}
	ImGui::PopID();
	ImGui::PopStyleVar();
}

struct category 
{
	const char* name;
};

static std::vector<category> categories =
{
	{ "Auto Clicker"},
	{ "Player Tweaks"},
	{ "Visuals"},
	{ "Aimbot"},
	{ "Settings"}
};

std::once_flag flag_load;

void prnt()
{
	std::cout << "from prnt fnc" << std::endl;
}

void set_unload()
{
	owlhook::start_unload = true;
}

void menu::render()
{
	ImGuiIO& io = ImGui::GetIO();

	std::call_once(flag_load, [&]() 
	{
		load_textures();

		ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(space_array_compressed_data,
			sizeof space_array_compressed_data, 20.0f);
	});
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static int current_category = 0;

	{
		ImVec2 window_size = { 650, 400 };

		ImGui::SetNextWindowSize(window_size);

		if (config::get_item("sync_color")->b)
		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4{config::get_item("global_color")->c.red, config::get_item("global_color")->c.green, config::get_item("global_color")->c.blue, config::get_item("global_color")->c.alpha});
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4{ config::get_item("global_color")->c.red, config::get_item("global_color")->c.green, config::get_item("global_color")->c.blue, config::get_item("global_color")->c.alpha });
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4{ config::get_item("title_bar_color")->c.red, config::get_item("title_bar_color")->c.green, config::get_item("title_bar_color")->c.blue, config::get_item("title_bar_color")->c.alpha });
			ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4{ config::get_item("title_bar_color")->c.red, config::get_item("title_bar_color")->c.green, config::get_item("title_bar_color")->c.blue, config::get_item("title_bar_color")->c.alpha });
		}
		
		
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 24.f);
		ImGui::Begin("Owl Hook | 0.1", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(2);

		ImGui::PushStyleColor(ImGuiCol_Border, ImColor(0, 0, 0, 255).Value);

		ImGui::BeginChild("##LeftSide", ImVec2(77, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoScrollbar);
		{
			for (unsigned int i = 0; i < categories.size(); i++) {
				bool selected = (current_category == i);

				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25.0f);
				if (selected)
				{
					if (config::get_item("sync_color")->b)
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ config::get_item("global_color")->c.red, config::get_item("global_color")->c.green, config::get_item("global_color")->c.blue, config::get_item("global_color")->c.alpha });
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ config::get_item("global_color")->c.red, config::get_item("global_color")->c.green, config::get_item("global_color")->c.blue, config::get_item("global_color")->c.alpha });
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ config::get_item("global_color")->c.red, config::get_item("global_color")->c.green, config::get_item("global_color")->c.blue, config::get_item("global_color")->c.alpha });
					}
					else
					{
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ config::get_item("active_tab_color")->c.red, config::get_item("active_tab_color")->c.green, config::get_item("active_tab_color")->c.blue, config::get_item("active_tab_color")->c.alpha });
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ config::get_item("active_tab_color")->c.red, config::get_item("active_tab_color")->c.green, config::get_item("active_tab_color")->c.blue, config::get_item("active_tab_color")->c.alpha });
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ config::get_item("active_tab_color")->c.red, config::get_item("active_tab_color")->c.green, config::get_item("active_tab_color")->c.blue, config::get_item("active_tab_color")->c.alpha });
					}
				}

				switch (i)
				{
					case 0: if (ImGui::ImageButton((void*)(intptr_t)mouse_texture, ImVec2(texture_width, texture_height))); break;
					case 1: if (ImGui::ImageButton((void*)(intptr_t)player_texture, ImVec2(texture_width, texture_height))); break;
					case 2: if (ImGui::ImageButton((void*)(intptr_t)visuals_texture, ImVec2(texture_width, texture_height))); break;
					case 3: if (ImGui::ImageButton((void*)(intptr_t)aim_texture, ImVec2(texture_width, texture_height))); break;
					case 4: if (ImGui::ImageButton((void*)(intptr_t)setting_texture, ImVec2(texture_width, texture_height))); break;
				}

				if (ImGui::IsItemActive())
				{
					current_category = i;
				}

				ImGui::PopStyleVar();
				if (selected)
				{
					ImGui::PopStyleColor(3);
				}

				if (i != categories.size()) ImGui::Dummy(ImVec2{ 0.0001f, 0.0f });

				if (selected) ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndChild();
		{
			ImGui::SameLine(0);

			ImGui::SameLine();
		}

		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{
			auto center = [](float avail_width, float element_width, float padding = 0) 
			{
				ImGui::SameLine((avail_width / 2) - (element_width / 2) + padding);
			};

			auto center_text = [&](const char* format, float spacing = 15, ImColor color = ImColor(255, 255, 255))
			{
				center(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(format).x);
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing);
				ImGui::TextColored(color.Value, format);
			};

			auto& data = categories[current_category];

			center_text(data.name, 0);
			ImGui::Separator();

			switch (current_category)
			{

			case 0: // Auto Clicker Shit
			{
				break;
			}
			case 1: // Player Tweak Shit
			{
				break;
			}
			case 2: // Visual Shit
			{
				break;
			}
			case 3: // Aim Bot Shit
			{
				break;
			}
			case 4: // Setting Shit
			{
				color_picker_checkbox("Sync UI Colors", (float*)&config::get_item("global_color")->c, &config::get_item("sync_color")->b, 1, 1);
				color_picker("Title Bar Color", (float*)&config::get_item("title_bar_color")->c, 2);
				color_picker("Active Tab Color", (float*)&config::get_item("active_tab_color")->c, 3);
				
				button("Unload From Memory", &set_unload, 1);
				button("Load Config", &config::load, 1);
				button("Save Config", &config::save, 1);

				break;
			}

			}
		}
		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::End();
	}
	ImGui::Render();
}