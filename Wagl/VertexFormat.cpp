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

int VertexFormat::getStride(int attributeNumber)
{
	
	if (stride == -1) {
		int stride = 0;
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