#pragma once

#include <string>
#include <vector>

enum value_type
{
	_INT, _FLOAT, _STRING, _BOOL, _COLOR
};

struct color4f
{
	float red;
	float green;
	float blue;
	float alpha;
};

class item
{
public:
	std::string name;
	value_type vt;
	int i;
	float f;
	bool b;
	std::string s;
	color4f c;

	item(std::string name, value_type vt, int i)
	{
		this->name = name;
		this->vt = vt;
		this->i = i;
	}

	item(std::string name, value_type vt, float f)
	{
		this->name = name;
		this->vt = vt;
		this->f = f;
	}

	item(std::string name, value_type vt, std::string s)
	{
		this->name = name;
		this->vt = vt;
		this->s = s;
	}

	item(std::string name, value_type vt, color4f c)
	{
		this->name = name;
		this->vt = vt;
		this->c = c;
	}

	item(std::string name, value_type vt, bool b)
	{
		this->name = name;
		this->vt = vt;
		this->b = b;
	}
};

inline std::vector<item*> all_items;

namespace config
{
	item* get_item(std::string name);

	void register_items();

	void save();
	void load();
}