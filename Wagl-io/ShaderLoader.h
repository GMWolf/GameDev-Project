#pragma once
#include <Shader.h>
#include <string>
#include "File.h"
class ShaderLoader
{
public:
	template<int type>
	static Shader<type>* Load(std::string file);

private:

	ShaderLoader();
	~ShaderLoader();
};

template<int type>
Shader<type>* ShaderLoader::Load(std::string file)
{
	std::string source;
	File::read(file, source);

	return new Shader<type>(source);
}
