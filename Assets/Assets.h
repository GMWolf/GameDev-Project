#pragma once
#include "AssetManager.h"
#include "MaterialLoader.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
class Assets
{
public:
	Assets();
	~Assets();

	AssetManager<Material> materials;
	AssetManager<wagl::Texture> textures;
	AssetManager<Mesh> meshs;
};

