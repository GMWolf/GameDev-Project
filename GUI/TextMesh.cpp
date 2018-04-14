#include "TextMesh.h"
#include "VBBuilder.h"

const wagl::VertexFormat TextMesh::format = {
	{ GL_FLOAT, 2, "position" },
	{ GL_FLOAT, 2, "texCoord" }
};


TextMesh::TextMesh():
	vb(format, GL_DYNAMIC_DRAW),
	va(vb)
{
	std::cout << "Textmesh constructed with vb "  << std::endl;
}


TextMesh::~TextMesh()
{
}

void TextMesh::update(std::string string, FontDescriptor& font)
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
		elements.emplace_back(i + 2);
		elements.emplace_back(i + 1);
		elements.emplace_back(i + 3);

		cursor += c.advance;
		i += 4;
	}

	wagl::VBBuilder builder(format);
	builder.set(0, positions);
	builder.set(1, uvs);
	builder.setElems(elements);
	builder.update(vb);
}

void TextMesh::submit()
{
	va.submit(vb.elementCount);
}
