#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(VertexFormat format, int usage) : format(format), usage(usage), vertexCount(0)
{
	glGenBuffers(2, buffers);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(2, buffers);
}

void VertexBuffer::setVertexData(const int vertCount, const void* data)
{
	int size = vertCount *  format.getStride();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setElementsData(const int vertCount, const void * data)
{
	vertexCount = vertCount;

	int size = vertCount * GetGLTypeSize(GL_UNSIGNED_INT);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}
