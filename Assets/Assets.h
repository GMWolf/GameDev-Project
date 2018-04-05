#pragma once
#include "MaterialLoader.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
class Assets
{
public:
	Assets();
	~Assets();

	AssetLoader<wagl::Texture> textureLoader;
	AssetManager<wagl::Texture> textures;

	AssetLoader<Material> materialLoader;
	AssetManager<Material> materials;

	AssetLoader<Mesh> meshLoader;
	AssetManager<Mesh> meshs;
};

