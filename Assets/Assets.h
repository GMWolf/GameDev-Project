#pragma once
#include "MaterialLoader.h"
#include "TextureLoader.h"
#include "MeshLoader.h"
#include "RenderMeshLoader.h"
#include "FontLoader.h"
#include <unordered_map>
#include <typeindex>

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
	AssetManager<Mesh> meshes;

	AssetLoader<RenderMesh> renderMeshLoader;
	AssetManager<RenderMesh> renderMeshes;

	AssetLoader<Font> fontLoader;
	AssetManager<Font> fonts;

private:
	std::unordered_map<std::type_index, void* > managers;
};

