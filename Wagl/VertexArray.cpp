#include "VertexArray.h"



VertexArray::VertexArray(VertexBuffer& vb)
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

VertexArray::VertexArray(VertexBuffer & vb, ShaderProgram & shd)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	vb.bind();

	int stride = vb.format.getStride();

	for (int i = 0; i < vb.format.attributes.size(); i++) {
		VertexAttribute vertAttrib = vb.format.attributes[i];

		GLint location = shd.GetAttribute(vertAttrib.alias).location;

		int offset = vb.format.getOffset(i);
		glVertexAttribPointer(i, vertAttrib.elementCount, vertAttrib.type, GL_FALSE, stride, (void*)offset);
		glEnableVertexAttribArray(i);
	}
	glBindVertexArray(0);
}



VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind()
{
	glBindVertexArray(vao);
}


