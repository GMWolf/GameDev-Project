#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <string>

class ShaderProgramLoader
{
public:

	static wagl::ShaderProgram* Load(std::string file);
	
private:
	ShaderProgramLoader();
	~ShaderProgramLoader();
};

