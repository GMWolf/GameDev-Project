#include "FontParser.h"
/*
void wagl::buildVB(const std::string& string, const FontDescriptor& font, VertexBuffer& vb)
{
	std::vector<glm::vec2> positions;
	std::vector<glm::vec2> uvs;
	std::vector<int> elements;
	int i = 0;
	float cursor = 0;
	for (char cs : string)
	{
		const Character c = font.chars[cs];

		//top left
		positions.emplace_back(cursor + c.xOffset, c.yOffset);
		uvs.emplace_back(c.x / (float)font.width, c.y / (float)font.height);

		//top right
		positions.emplace_back(cursor + c.xOffset + c.width, c.yOffset);
		uvs.emplace_back((c.x + c.width) / (float)font.width, c.y / (float)font.height);

		//bottom right
		positions.emplace_back(cursor + c.xOffset + c.width, c.yOffset + c.height);
		uvs.emplace_back((c.x + c.width) / (float)font.width, (c.y + c.height) / (float)font.height);

		//bottom left
		positions.emplace_back(cursor + c.xOffset, c.yOffset + c.height);
		uvs.emplace_back(c.x / (float)font.width, (c.y + c.height) / (float)font.height);

		elements.emplace_back(i + 0);
		elements.emplace_back(i + 1);
		elements.emplace_back(i + 2);
		elements.emplace_back(i + 1);
		elements.emplace_back(i + 2);
		elements.emplace_back(i + 3);

		cursor += c.advance;
		i += 4;
	}

	VBBuilder builder(textFormat);
	builder.set(0, positions);
	builder.set(1, uvs);
	builder.setElems(elements);
	builder.update(vb);
}
*/
#include <iosfwd>
#include <sstream>

void parseFontCommon(std::stringstream& line, FontDescriptor& font)
{
	//https://www.gamedev.net/forums/topic/330742-quick-tutorial-variable-width-bitmap-fonts/
	std::string r;
	while (!line.eof())
	{
		line >> r;
		const int i = r.find('=');
		const std::string key = r.substr(0, i);
		const std::string value = r.substr(i + 1);
		if (key == "lineHeight")
		{
			font.lineHeight = std::stoi(value);
		}
		else if (key == "base")
		{
			font.base = std::stoi(value);
		}
		else if (key == "scaleW")
		{
			font.width = std::stoi(value);
		}
		else if (key == "scaleH")
		{
			font.height = std::stoi(value);
		}
		else if (key == "pages")
		{
			font.pages = std::stoi(value);
		}
	}
}

void parseFontChar(std::stringstream& line, FontDescriptor& font)
{
	//https://www.gamedev.net/forums/topic/330742-quick-tutorial-variable-width-bitmap-fonts/
	std::string r;
	unsigned int charId = 0;
	while (!line.eof())
	{
		line >> r;

		const int i = r.find('=');
		const std::string key = r.substr(0, i);
		const std::string value = r.substr(i + 1);
		if (key == "id")
		{
			charId = std::stoi(value);
		}
		else if (key == "x")
		{
			font.chars[charId].x = std::stoi(value);
		}
		else if (key == "y")
		{
			font.chars[charId].y = std::stoi(value);
		}
		else if (key == "width")
		{
			font.chars[charId].width = std::stoi(value);
		}
		else if (key == "height")
		{
			font.chars[charId].height = std::stoi(value);
		}
		else if (key == "xoffset")
		{
			font.chars[charId].xOffset = std::stof(value);
		}
		else if (key == "yoffset")
		{
			font.chars[charId].yOffset = std::stof(value);
		}
		else if (key == "xadvance")
		{
			font.chars[charId].advance = std::stof(value);
		}
		else if (key == "page")
		{
			font.chars[charId].page = std::stoi(value);
		}
	}
}

bool parseFont(std::istream& s, FontDescriptor& font)
{
	//https://www.gamedev.net/forums/topic/330742-quick-tutorial-variable-width-bitmap-fonts/
	while (!s.eof())
	{
		std::stringstream line;
		std::string lineStr;
		std::getline(s, lineStr);

		line << lineStr;

		std::string r;
		line >> r;

		if (r == "common")
		{
			parseFontCommon(line, font);
		}
		else if (r == "char")
		{
			parseFontChar(line, font);
		}
	}
	return true;
}
