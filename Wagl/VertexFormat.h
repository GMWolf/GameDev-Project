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

	int getStride(int attributeNumber);
	int getOffset(int attributeNumber);
private:
	void markDirty();

	std::vector<VertexAttribute> attributes;
	mutable int stride;
	mutable int* offsets;
};

int GetGLTypeSize(int type)
{
	switch (type) {
	case GL_FLOAT: return 32;
	case GL_INT: return 32;
	case GL_UNSIGNED_INT: return 32;
	case GL_BYTE:return 8;
	case GL_UNSIGNED_BYTE:return 8;
	case GL_SHORT: return 16;
	case GL_UNSIGNED_SHORT: return 16;
	case GL_HALF_FLOAT: return 16;
	case GL_DOUBLE:return 64;
	}
	throw std::invalid_argument("Unknown type " + type);
}