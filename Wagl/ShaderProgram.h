#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
class ShaderProgram
{
public:
	ShaderProgram(Shader<GL_VERTEX_SHADER>& vertex, Shader<GL_FRAGMENT_SHADER>& fragment);
	~ShaderProgram();

	int GetAttributeLocation(std::string attribute);
	int GetUniformLocation(std::string uniform);
	void use();

private:

	void link();

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint program;
};

