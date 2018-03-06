#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexFormat.h"

class VertexBuffer
{
public:
	friend class Model;
	friend class VertexArray;

	VertexBuffer(VertexFormat format, int usage);
	~VertexBuffer();

	void setVertexData(const int vertexCount, const void* data);
	void setElementsData(const int vertexCount, const void* data);

	void bind();

private:
	int usage;
	int vertexCount;
	VertexFormat format;

	union {
		struct {
			GLuint vbo; //vertex buffer object
			GLuint ebo; //element buffer object
		};

		GLuint buffers[2];
	};
	
};