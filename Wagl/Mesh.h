#pragma once
#include "VertexBuffer.h"
#include <Vector3.h>
#include <vector>
class Mesh
{
public:
	Mesh();
	~Mesh();

	

private:

	VertexFormat format;
	VertexBuffer vb;
};

