#include "VertexArray.h"

wagl::VertexArray::VertexArray(VertexBuffer& vb)
{
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);
	vb.bind();

	const int stride = vb.format.getStride();

	for (int i = 0; i < vb.format.attributes.size(); i++) {
		const VertexAttribute vertAttrib = vb.format.attributes[i];

		const int offset = vb.format.getOffset(i);
		glVertexAttribPointer(i, vertAttrib.elementCount, vertAttrib.type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);
}

wagl::VertexArray::VertexArray(VertexBuffer & vb, ShaderProgram & shd)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vb.bind();

	int stride = vb.format.getStride();

	for (int i = 0; i < vb.format.attributes.size(); i++) {
		VertexAttribute vertAttrib = vb.format.attributes[i];

		int offset = vb.format.getOffset(i);
		glVertexAttribPointer(i, vertAttrib.elementCount, vertAttrib.type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
}



wagl::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void wagl::VertexArray::bind() const
{
	glBindVertexArray(vao);
}

void wagl::VertexArray::unbind()
{
	glBindVertexArray(0);
}

void wagl::VertexArray::submit(unsigned int elementCount) const
{
	bind();
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)0);
	unbind();
}
