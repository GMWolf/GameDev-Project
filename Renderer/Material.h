#pragma once
#include "Texture.h"

class Material
{
public:
	Material();
	~Material();

	bool operator==(const Material& rhs) const
	{
		return (diffuse == rhs.diffuse) && (normal == rhs.normal);
	}

	wagl::Texture* diffuse;
	wagl::Texture* normal;
};

