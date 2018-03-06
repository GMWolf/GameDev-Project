#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "ShaderProgram.h"
class VertexArray
{
public:
	VertexArray(VertexBuffer& vb);
	VertexArray(VertexBuffer& vb, ShaderProgram& shd);
	~VertexArray();

	void bind() const;

private:
	GLuint vao{};
};

