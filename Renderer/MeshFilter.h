#pragma once
#include <Component.h>
#include "Mesh.h"

COMPONENT(MeshFilter, 16) {

	MeshFilter() : mesh(nullptr) {
	};

	MeshFilter(Mesh* mesh) : mesh(mesh) {
	};

	Mesh* mesh;
};