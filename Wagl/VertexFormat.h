#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

struct VertexAttribute
{
	VertexAttribute(int type, int elementCount, std::string alias);

	int type;
	int elementCount;
	std::string alias;

	int size();

	static const VertexAttribute POSITION;
	static const VertexAttribute TEXTURE_COORDINATES;
	static const VertexAttribute COLOUR;
	static const VertexAttribute NORMAL;
};

class VertexFormat
{
public:
	VertexFormat();
	~VertexFormat();
	
	VertexFormat& add(VertexAttribute attribute);

	int getStride();
	int getOffset(int attributeNumber);

	std::vector<VertexAttribute> attributes;
private:
	void markDirty();
	mutable int stride;
	mutable int* offsets;
};

int GetGLTypeSize(int type);