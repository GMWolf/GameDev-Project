#include "stdafx.h"
#include "Assets.h"


Assets::Assets() : materials(*this), textures(*this), meshs(*this)
{
}


Assets::~Assets()
{
}
