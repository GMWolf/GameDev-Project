#pragma once
#include "AssetHandle.h"
#include <FontParser.h>
#include <Texture.h>

class Font
{
public:

	FontDescriptor fontDescriptor;
	AssetHandle<wagl::Texture> texture;
};

