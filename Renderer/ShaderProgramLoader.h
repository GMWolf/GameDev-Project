#pragma once
#include <string>
#include "ShaderProgram.h"

class ShaderProgramLoader 
{
public:
	static wagl::ShaderProgram* load(std::string file);
};
