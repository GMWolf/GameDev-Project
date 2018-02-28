#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "ShaderProgram.h"
class Model
{
public:
	Model(VertexBuffer* vb, ShaderProgram* shader);
	~Model();

	void setMesh(VertexBuffer* vb);
	void setShader(ShaderProgram* shader);

	void bindAttributes();

	void draw();

private:

	VertexBuffer * vb;
	ShaderProgram * shader;
	GLuint vao;
	bool attribsBounded;
};

