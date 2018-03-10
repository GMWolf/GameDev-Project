#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <initializer_list>

namespace wagl {

	struct VertexAttribute
	{
		VertexAttribute(GLenum type, GLsizei elementCount, std::string alias);

		GLenum type;
		GLsizei elementCount;
		std::string alias;

		int size() const;

		bool operator==(const VertexAttribute& rhs) const;
	};

	class VertexFormat
	{
	public:
		VertexFormat();
		~VertexFormat();

		VertexFormat(std::initializer_list<const VertexAttribute> attributes);

		VertexFormat& add(VertexAttribute attribute);

		const VertexAttribute& findAttribute(std::string alias, bool& found) const;

		int getAttributeNumber(VertexAttribute attribute) const;

		int getStride() const;
		int getOffset(int attributeNumber) const;

		std::vector<VertexAttribute> attributes;
	private:
		void markDirty();
		mutable int stride;
		mutable int* offsets;
	};

	int GetGLTypeSize(int type);
}