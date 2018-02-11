#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexFormat.h"
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void bufferData(const GLsizeiptr size, const void* data);

	GLuint vbo;
};

