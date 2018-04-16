#include "stdafx.h"
#include "ShaderProgramLoader.h"
#include "json.hpp"
#include <fstream>
#include <Shader.h>
#include <ShaderProgram.h>

wagl::ShaderProgram* ShaderProgramLoader::load(std::string file)
{
	std::ifstream i(file);
	nlohmann::json j;
	i >> j;


	std::ifstream vertexFile(j["vertex"].get<std::string>());
	std::ifstream fragmentFile (j["fragment"].get<std::string>());

	const std::string vertexSource((std::istreambuf_iterator<char>(vertexFile)), std::istreambuf_iterator<char>());
	const std::string fragmentSource((std::istreambuf_iterator<char>(fragmentFile)), std::istreambuf_iterator<char>());

	wagl::Shader<GL_VERTEX_SHADER>* vs = new wagl::Shader<GL_VERTEX_SHADER>(vertexSource);
	wagl::Shader<GL_FRAGMENT_SHADER>* fs = new wagl::Shader<GL_FRAGMENT_SHADER>(fragmentSource);

	wagl::Shader<GL_GEOMETRY_SHADER>* gs = nullptr;
	if (j.find("geometry") != j.end())
	{
		std::ifstream geometryFile(j["geometry"].get<std::string>());
		const std::string geometrySource((std::istreambuf_iterator<char>(geometryFile)), std::istreambuf_iterator<char>());
		gs = new wagl::Shader<GL_GEOMETRY_SHADER>(geometrySource);
	}


	wagl::ShaderProgram* p = new wagl::ShaderProgram(vs, gs, fs);

	delete vs;
	delete fs;
	delete gs;
	return p;
}
