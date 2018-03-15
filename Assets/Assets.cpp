#include "stdafx.h"
#include "Assets.h"


Assets::Assets() : materialLoader(textures), materials(materialLoader), textures(textureLoader), meshs(meshLoader)
{
}


Assets::~Assets()
{
}
