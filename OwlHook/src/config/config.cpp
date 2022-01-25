#include "config.h"

#include "../util/vector_util.h"

#include <windows.h>
#include <lmcons.h>
#include <string>
#include <sstream>
#include "INIReader.h"
#include <fstream>
#include <Lmcons.h>

void config::register_items()
{
	{ // UI Settings
		all_items.push_back(new item("active_tab_color", _COLOR,
			color4f{ 145.f / 255.f, 94.f / 255.f, 174.f / 255.f, 100.f / 255.f}));
		all_items.push_back(new item("title_bar_color", _COLOR,
			color4f{ 145.f / 255.f, 94.f / 255.f, 174.f / 255.f, 100.f / 255.f }));
		all_items.push_back(new item("global_color", _COLOR,
			color4f{ 145.f / 255.f, 94.f / 255.f, 174.f / 255.f, 100.f / 255.f }));
		all_items.push_back(new item("sync_color", _BOOL, false));
	}
}

item* config::get_item(std::string name)
{
	for (item* item : all_items) 
	{
		if (item->name == name)
		{
			return item;
		}
	}
	return nullptr;
}

std::string user_name()
{
	char buffer[UNLEN + 1]{};
	DWORD len = UNLEN + 1;
	if (::GetUserNameA(buffer, &len)) return buffer;
	else return {}; // or: return "" ;
}

std::string config_location = "C:\\Users\\" + user_name() + "\\owlhook_config.ini";

void config::save()
{
	std::ofstream config_file;
	config_file.open(config_location);
	config_file.clear();

	for (item* item : all_items)
	{
		config_file << "[" + item->name << "]" << std::endl;

		config_file << "type = " << item->vt << std::endl;
		
		switch (item->vt)
		{
			case _INT: config_file << "value = " << item->i << std::endl; break;
			case _FLOAT: config_file << "value = " << item->f << std::endl; break;
			case _STRING: config_file << "value = " << item->s << std::endl; break;
			case _BOOL: config_file << "value = " << item->b << std::endl; break;
			case _COLOR:
			{
				config_file << "red value = " << item->c.red << std::endl;
				config_file << "green value = " << item->c.green << std::endl;
				config_file << "blue value = " << item->c.blue << std::endl;
				config_file << "alpha value = " << item->c.alpha << std::endl;
			
				break;
			}
		}

		config_file << std::endl;
	}

	config_file.close();
}

void config::load()
{
	INIReader reader(config_location);

	if (reader.ParseError() != 0) return;

	for (item* item : all_items)
	{
		int i = reader.GetInteger(item->name, "type", -1);
		value_type type = static_cast<value_type>(i);
		
		switch (type)
		{
			case _INT: item->i = reader.GetInteger(item->name, "value", -1); break;
			case _FLOAT: item->f = reader.GetFloat(item->name, "value", -1.f); break;
			case _STRING: item->s = reader.Get(item->name, "value", "UNKNOWN"); break;
			case _BOOL: item->b = reader.GetBoolean(item->name, "value", false); break;
			case _COLOR:
			{
				item->c.red = reader.GetFloat(item->name, "red value", false);
				item->c.green = reader.GetFloat(item->name, "green value", false);
				item->c.blue = reader.GetFloat(item->name, "blue value", false);
				item->c.alpha = reader.GetFloat(item->name, "alpha value", false);

				break;
			}
		}

	}
}