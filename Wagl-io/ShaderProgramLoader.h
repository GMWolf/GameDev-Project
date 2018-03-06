#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <string>
#include "ShaderLoader.h"

class ShaderProgramLoader
{
public:

	static ShaderProgram* Load(std::string file);
	
private:
	ShaderProgramLoader();
	~ShaderProgramLoader();
};

