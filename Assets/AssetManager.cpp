#include "stdafx.h"
#include "AssetManager.h"
#include "../Renderer/meshLoader.h"
#include "../Wagl-io/ImageLoader.h"


AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
	for(auto o : meshMap)
	{
		delete o.second;
	}

	for(auto o : textureMap)
	{
		delete o.second;
	}
}

Mesh* AssetManager::getMesh(std::string file)
{
	
	if (meshMap.find(file) == meshMap.end())
	{
		Mesh* mesh = MeshLoader::LoadObj(file);
		meshMap[file] = mesh;
		return mesh;
	} else
	{
		return meshMap[file];
	}
}

void AssetManager::manage(std::string name, Mesh* mesh)
{
	meshMap[name] = mesh;
}

wagl::Texture* AssetManager::getTexture(std::string file)
{
	if (textureMap.find(file) == textureMap.end())
	{
		wagl::Texture* texture = ImageLoader::Load(file);
		textureMap[file] = texture;
		return texture;
	}
	else
	{
		return textureMap[file];
	}
}
