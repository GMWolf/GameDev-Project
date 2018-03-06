#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

template<int type>
class Shader
{
public:
	friend class ShaderProgram;

	Shader(std::string source)
	{
		const char* cstr = source.c_str();

		glShader = glCreateShader(type);
		glShaderSource(glShader, 1, &cstr, nullptr);
		glCompileShader(glShader);

		GLint status;
		glGetShaderiv(glShader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			std::cout << "Could not compile shader" << std::endl;

			char error[2048];
			glGetShaderInfoLog(glShader, sizeof(error), nullptr, error);
			std::cout << error << std::endl;
		}
	}
	~Shader()
	{
		glDeleteShader(glShader);
	}
private:

	
	GLuint glShader;
};

