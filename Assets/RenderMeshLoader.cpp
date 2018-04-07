#include "stdafx.h"
#include "RenderMeshLoader.h"
#include "MeshLoader.h"

AssetLoader<RenderMesh>::AssetLoader(AssetManager<Mesh>& meshes) : meshes(meshes)
{
}



void AssetLoader<RenderMesh>::load(std::string fileName, RenderMesh& renderMesh) const
{
	AssetHandle<Mesh> meshHandle = meshes.get(fileName);
	Mesh& mesh = meshHandle();

	renderMesh.setData(mesh);
}
