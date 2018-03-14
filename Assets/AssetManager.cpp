#include "stdafx.h"
#include "AssetManager.h"
#include "MeshLoader.h"
#include "ImageLoader.h"
#include "ShaderProgramLoader.h"


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

wagl::ShaderProgram* AssetManager::getShaderProgram(std::string file)
{
	if (shaderPrograms.find(file) == shaderPrograms.end())
	{
		wagl::ShaderProgram* shader = ShaderProgramLoader::Load(file);
		shaderPrograms[file] = shader;
		return shader;
	} else
	{
		return shaderPrograms[file];
	}
}
