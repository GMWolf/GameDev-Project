#pragma once
#include <Component.h>
#include "Mesh.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter() : mesh(nullptr), texture(nullptr)
	{
	};

	MeshFilter(Mesh* mesh, Texture* texture) : mesh(mesh), texture(texture)
	{
	};

	Mesh* mesh;
	Texture* texture;
};