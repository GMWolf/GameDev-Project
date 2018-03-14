#pragma once
#include <Shader.h>
#include <string>
#include "File.h"
class ShaderLoader
{
public:
	template<int type>
	static wagl::Shader<type>* Load(std::string file);

private:

	ShaderLoader();
	~ShaderLoader();
};

template<int type>
wagl::Shader<type>* ShaderLoader::Load(std::string file)
{
	std::string source;
	File::read(file, source);

	return new wagl::Shader<type>(source);
}
