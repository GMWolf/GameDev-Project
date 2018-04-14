#include "stdafx.h"
#include "Assets.h"


Assets::Assets() : 
	textures(textureLoader),
	materialLoader(textures), materials(materialLoader),
	meshes(meshLoader),
	renderMeshLoader(meshes), renderMeshes(renderMeshLoader),
	fontLoader(textures),
	fonts(fontLoader)
{
}


Assets::~Assets()
{
}
