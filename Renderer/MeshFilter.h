#pragma once
#include <Component.h>
#include "Mesh.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter() : mesh(nullptr), texture(nullptr)
	{
	};

	MeshFilter(Mesh* mesh, wagl::Texture* texture) : mesh(mesh), texture(texture)
	{
	};

	Mesh* mesh;
	wagl::Texture* texture;
	wagl::Texture* normal;
};