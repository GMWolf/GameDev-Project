#include "VertexFormat.h"



VertexFormat::VertexFormat()
{
	markDirty();
}


VertexFormat::~VertexFormat()
{
}

VertexFormat & VertexFormat::add(VertexAttribute attribute)
{
	attributes.emplace_back(attribute);
	markDirty();
	return *this;
}

int VertexFormat::getStride()
{
	if (stride < 0) {
		stride = 0;
		for (int i = 0; i < attributes.size(); i++) {
			stride += attributes[i].size();
		}
	}

	return stride;
}

int VertexFormat::getOffset(int attributeNumber)
{
	if (offsets == nullptr) {
		offsets = new int[attributes.size()];
		int offset = 0;
		for (int i = 0; i < attributes.size(); i++) {
			offsets[i] = offset;
			offset += attributes[i].size();
		}
	}

	return offsets[attributeNumber];
}

void VertexFormat::markDirty()
{
	stride = -1;
	delete[] offsets;
	offsets = nullptr;
}



VertexAttribute::VertexAttribute(int type, int elementCount, std::string alias)
	: type(type), elementCount(elementCount), alias(alias)
{
}

inline int VertexAttribute::size() {
	return GetGLTypeSize(type) * elementCount;
}

const VertexAttribute VertexAttribute::POSITION = { GL_FLOAT, 3, "position" };
const VertexAttribute VertexAttribute::TEXTURE_COORDINATES = { GL_FLOAT, 2, "tex_coord" };
const VertexAttribute VertexAttribute::COLOUR = { GL_FLOAT, 4, "colour" };
const VertexAttribute VertexAttribute::NORMAL = { GL_FLOAT, 3, "normal" };

int GetGLTypeSize(int type)
{
	switch (type) {
	case GL_FLOAT: return 4;
	case GL_INT: return 4;
	case GL_UNSIGNED_INT: return 4;
	case GL_BYTE:return 1;
	case GL_UNSIGNED_BYTE:return 1;
	case GL_SHORT: return 2;
	case GL_UNSIGNED_SHORT: return 2;
	case GL_HALF_FLOAT: return 2;
	case GL_DOUBLE:return 8;
	}
	throw std::invalid_argument("Unknown type " + type);
}
