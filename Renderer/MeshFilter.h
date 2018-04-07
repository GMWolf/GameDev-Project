#pragma once
#include <Component.h>
#include "Mesh.h"
#include "AssetHandle.h"
#include "Material.h"
#include "RenderMesh.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter()
	{
	};

	MeshFilter(AssetHandle<RenderMesh> mesh, AssetHandle<Material> material) : mesh(mesh), material(material)
	{
	};

	AssetHandle<RenderMesh> mesh;
	AssetHandle<Material> material;
};