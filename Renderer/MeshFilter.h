#pragma once
#include <Component.h>
#include "Mesh.h"
#include "AssetHandle.h"
#include "Material.h"
#include "RenderMesh.h"
#include <ComponentLoader.h>
#include <Assets.h>

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

class MeshFilterLoader : public ComponentLoader {
public:
	MeshFilterLoader(Assets& assets) : assets(assets) {

	}

	void load(nlohmann::json& j, void* c) override {
		MeshFilter* mf = static_cast<MeshFilter*>(c);
		
		mf->mesh = assets.get<RenderMesh>(j["mesh"].get<std::string>());
		mf->material = assets.get<Material>(j["material"].get<std::string>());
	}

private:
	Assets& assets;

};