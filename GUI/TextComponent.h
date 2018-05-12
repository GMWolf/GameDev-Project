#pragma once
#include <Component.h>
#include <VertexBuffer.h>
#include <VertexArray.h>
#include "AssetHandle.h"
#include "Font.h"


COMPONENT(TextComponent, 8, 13)
{

	TextComponent() : string("")
	{
	};

	TextComponent(std::string str) : string(str)
	{
	}

	std::string string;
};
