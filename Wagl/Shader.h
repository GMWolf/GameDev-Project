#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
template<int type>
class Shader
{
public:
	friend class ShaderProgram;

	Shader(std::string file)
	{
		std::string source;
		loadFile(file, source);
		const char* cstr = source.c_str();

		glShader = glCreateShader(type);
		glShaderSource(glShader, 1, &cstr, NULL);
		glCompileShader(glShader);

		GLint status;
		glGetShaderiv(glShader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE) {
			std::cout << "Could not compile shader" << std::endl;

			char error[2048];
			glGetShaderInfoLog(glShader, sizeof(error), NULL, error);
			std::cout << error << std::endl;
		}
		else {
			std::cout << "Loaded " << file << std::endl;
		}
	}
	~Shader()
	{
	}
private:

	bool loadFile(std::string file, std::string & string)
	{
		std::ifstream is(file);
		if (!is) {
			std::cout << "Could not open " << file << std::endl;
			return false;
		}

		string.assign((std::istreambuf_iterator<char>(is)), (std::istreambuf_iterator<char>()));
		is.close();
		return true;
	}
	GLuint glShader;
};

