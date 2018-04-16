#include "stdafx.h"
#include "RenderMeshLoader.h"
#include "RenderMesh.h"


RenderMeshLoader::RenderMeshLoader(Assets& assets) : assets(assets)
{
}


RenderMeshLoader::~RenderMeshLoader()
{
}

void RenderMeshLoader::load(std::string file, void* location)
{
	RenderMesh* rm = new (location) RenderMesh;
	Mesh& mesh = assets.resolve(assets.get<Mesh>(file));
	rm->setData(mesh);
}
