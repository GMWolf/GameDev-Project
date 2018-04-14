#pragma once
#include "VertexBuffer.h"
#include "VertexArray.h"
#include <FontParser.h>
class TextMesh
{
public:
	TextMesh();
	~TextMesh();

	const static wagl::VertexFormat format;

	void update(std::string string, FontDescriptor& font);

	void submit();
private:
	wagl::VertexBuffer vb;
	wagl::VertexArray va;
};

