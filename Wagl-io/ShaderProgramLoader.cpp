#include "stdafx.h"
#include <json.hpp>
#include "ShaderProgramLoader.h"
#include "File.h"
#include "ShaderLoader.h"

using json = nlohmann::json;

ShaderProgram * ShaderProgramLoader::Load(std::string file)
{
	std::string str;
	File::read(file, str);

	json j = json::parse(str);

	const std::string vertexFile = j["vertex"].get<std::string>();
	const std::string fragmentFile = j["fragment"].get<std::string>();

	Shader<GL_VERTEX_SHADER>* vs = ShaderLoader::Load<GL_VERTEX_SHADER>(vertexFile);
	Shader<GL_FRAGMENT_SHADER>* fs = ShaderLoader::Load<GL_FRAGMENT_SHADER>(fragmentFile);

	Shader<GL_GEOMETRY_SHADER>* gs = nullptr;
	if (j.find("geometry") != j.end())
	{
		const std::string geometryFile = j["geometry"].get<std::string>();
		gs = ShaderLoader::Load<GL_GEOMETRY_SHADER>(geometryFile);
	}


	ShaderProgram* p = new ShaderProgram(vs, gs, fs);
	delete vs;
	delete fs;
	delete gs;
	return p;
}

ShaderProgramLoader::ShaderProgramLoader()
{
}


ShaderProgramLoader::~ShaderProgramLoader()
{
}
