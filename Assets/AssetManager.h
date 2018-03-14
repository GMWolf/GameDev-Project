#pragma once
#include <map>
#include "Texture.h"
#include "Mesh.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	Mesh* getMesh(std::string file);
	void manage(std::string name, Mesh* mesh);

	wagl::Texture* getTexture(std::string file);

	wagl::ShaderProgram* getShaderProgram(std::string file);

private:
	std::map<std::string, Mesh*> meshMap;
	std::map<std::string, wagl::Texture*> textureMap;
	std::map<std::string, wagl::ShaderProgram*> shaderPrograms;
};

