#pragma once
#include <string>


struct Character
{
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
	unsigned short page;

	float xOffset;
	float yOffset;

	float advance;

	Character() : x(0), y(0), width(0), height(0), xOffset(0), yOffset(0), advance(0)
	{
	}
};

struct FontDescriptor
{
	unsigned short lineHeight;
	unsigned short base;
	unsigned short width;
	unsigned short height;
	unsigned short pages;
	Character chars[256];
};

void parseFontCommon(std::stringstream& line, FontDescriptor& font);

void parseFontChar(std::stringstream& line, FontDescriptor& font);

bool parseFont(std::istream& s, FontDescriptor& font);