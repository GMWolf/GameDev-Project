#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"
#include "ShaderProgram.h"
class Model
{
public:
	Model(Mesh* mesh, ShaderProgram* shader);
	~Model();

	void setMesh(Mesh* mesh);
	void setShader(ShaderProgram* shader);

	void bindAttributes();

	void draw();

private:

	Mesh * mesh;
	ShaderProgram * shader;
	GLuint vao;
	bool attribsBounded;
};

