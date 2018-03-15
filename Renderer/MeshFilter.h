#pragma once
#include <Component.h>
#include "Mesh.h"
#include "AssetHandle.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter()
	{
	};

	MeshFilter(AssetHandle<Mesh> mesh, AssetHandle<wagl::Texture> texture) : mesh(mesh), texture(texture)
	{
	};

	AssetHandle<Mesh> mesh;
	AssetHandle<wagl::Texture> texture;
	AssetHandle<wagl::Texture> normal;
	AssetHandle<wagl::Texture> roughness;
};