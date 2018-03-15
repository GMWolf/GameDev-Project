#pragma once
#include <Component.h>
#include "Mesh.h"
#include "AssetHandle.h"
#include "Material.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter()
	{
	};

	MeshFilter(AssetHandle<Mesh> mesh, AssetHandle<Material> material) : mesh(mesh), material(material)
	{
	};

	AssetHandle<Mesh> mesh;
	AssetHandle<Material> material;
};