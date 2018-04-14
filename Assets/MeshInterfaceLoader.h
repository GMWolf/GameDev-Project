#pragma once
#include "AssetManager.h"
#include "BulletCollision/CollisionShapes/btStridingMeshInterface.h"
#include "Mesh.h"



template<>
class AssetLoader<btStridingMeshInterface>
{
public:

	explicit AssetLoader(AssetManager<Mesh>& meshes);

	void load(std::string file, btStridingMeshInterface& location) const;

private:

	AssetManager<Mesh>& meshes;
};

