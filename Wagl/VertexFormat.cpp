#include "VertexFormat.h"
#include <iostream>


wagl::VertexFormat::VertexFormat()
{
	markDirty();
}


wagl::VertexFormat::~VertexFormat()
{
}

wagl::VertexFormat::VertexFormat(std::initializer_list<const VertexAttribute> attributes) {
	for (VertexAttribute a : attributes) {
		add(a);
	}
	markDirty();
}

wagl::VertexFormat & wagl::VertexFormat::add(VertexAttribute attribute)
{
	attributes.emplace_back(attribute);
	markDirty();
	return *this;
}

const wagl::VertexAttribute & wagl::VertexFormat::findAttribute(std::string alias, bool& found) const
{
	for (VertexAttribute attribute : attributes) {
		if (attribute.alias == alias) {
			found = true;
			return attribute;
		}
	}

	found = false;
	return attributes.at(0);
}

int wagl::VertexFormat::getAttributeNumber(const VertexAttribute attribute) const
{
	for (int i = 0; i < attributes.size(); i++) {
		if (attributes[i] == attribute) {
			return i;
		}
	}
	return -1;
}

int wagl::VertexFormat::getStride() const 
{
	if (stride < 0) {
		stride = 0;
		for (int i = 0; i < attributes.size(); i++) {
			stride += attributes.at(i).size();
		}
	}

	return stride;
}

int wagl::VertexFormat::getOffset(int attributeNumber) const
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

void wagl::VertexFormat::markDirty()
{
	stride = -1;
	delete[] offsets;
	offsets = nullptr;
}



wagl::VertexAttribute::VertexAttribute(GLenum type, GLsizei elementCount, std::string alias)
	: type(type), elementCount(elementCount), alias(alias)
{
}

inline int wagl::VertexAttribute::size() const {
	return GetGLTypeSize(type) * elementCount;
}

bool wagl::VertexAttribute::operator==(const VertexAttribute & rhs) const
{
	return type == rhs.type && elementCount == rhs.elementCount && alias == rhs.alias;
}

#define GENERATE_VEC_CASES(base, baseSize) \
case base##_##VEC2: return (baseSize * 2); \
case base##_##VEC3: return (baseSize * 3); \
case base##_##VEC4: return (baseSize * 4);

#define GENERATE_MAT_CASES(base, baseSize) \
case base##_##MAT2: return (baseSize * 4); \
case base##_##MAT3: return (baseSize * 9); \
case base##_##MAT4: return (baseSize * 16); \
case base##_##MAT2x3: return (baseSize * 6); \
case base##_##MAT2x4: return (baseSize * 8); \
case base##_##MAT3x2: return (baseSize * 6); \
case base##_##MAT3x4: return (baseSize * 12); \
case base##_##MAT4x2: return (baseSize * 8); \
case base##_##MAT4x3: return (baseSize * 12);

int wagl::GetGLTypeSize(int type)
{
	switch (type) {
	case GL_FLOAT: return 4;
		GENERATE_VEC_CASES(GL_FLOAT, 4)
		GENERATE_MAT_CASES(GL_FLOAT, 4)
	case GL_INT: return 4;
		GENERATE_VEC_CASES(GL_INT, 4)
	case GL_UNSIGNED_INT: return 4;
		GENERATE_VEC_CASES(GL_UNSIGNED_INT, 4)
	case GL_BYTE:return 1;
	case GL_UNSIGNED_BYTE:return 1;
	case GL_SHORT: return 2;
	case GL_UNSIGNED_SHORT: return 2;
	case GL_HALF_FLOAT: return 2;
	case GL_DOUBLE:return 8;
		GENERATE_VEC_CASES(GL_DOUBLE, 8)
		GENERATE_MAT_CASES(GL_DOUBLE, 4)
	default: 
		std::cout << type << std::endl;
		throw std::invalid_argument("Unknown type " + type);
	}
}
