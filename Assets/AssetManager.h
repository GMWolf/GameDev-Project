#pragma once
#include <map>
#include "../Renderer/Mesh.h"
#include "Texture.h"

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	Mesh* getMesh(std::string file);
	void manage(std::string name, Mesh* mesh);

	Texture* getTexture(std::string file);

private:
	std::map<std::string, Mesh*> meshMap;
	std::map<std::string, Texture*> textureMap;
};

