#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "ShaderProgram.h"
class Model
{
public:
	Model(VertexBuffer* mesh, ShaderProgram* shader);
	~Model();

	void setMesh(VertexBuffer* mesh);
	void setShader(ShaderProgram* shader);

	void bindAttributes();

	void draw();

private:

	VertexBuffer * mesh;
	ShaderProgram * shader;
	GLuint vao;
	bool attribsBounded;
};

