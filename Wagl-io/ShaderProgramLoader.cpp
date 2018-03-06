#include "stdafx.h"
#include <json.hpp>
#include "ShaderProgramLoader.h"
#include "File.h"

using json = nlohmann::json;

ShaderProgram * ShaderProgramLoader::Load(std::string file)
{
	std::string str;
	File::read(file, str);

	json j = json::parse(str);
	
	std::string vertexFile = j["vertex"].get<std::string>();
	std::string fragmentFile = j["fragment"].get<std::string>();

	Shader<GL_VERTEX_SHADER> vs = ShaderLoader::Load<GL_VERTEX_SHADER>(vertexFile);
	Shader<GL_FRAGMENT_SHADER> fs = ShaderLoader::Load<GL_FRAGMENT_SHADER>(fragmentFile);

	return new ShaderProgram(vs, fs);
}

ShaderProgramLoader::ShaderProgramLoader()
{
}


ShaderProgramLoader::~ShaderProgramLoader()
{
}
