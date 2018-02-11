#pragma once
#include "VertexBuffer.h"
#include <Vector3.h>
#include <vector>
class Mesh
{
public:
	Mesh(VertexFormat format, VertexBuffer buffer);
	~Mesh();

private:

	VertexFormat format;
	VertexBuffer vb;
};

