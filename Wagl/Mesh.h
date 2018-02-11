#pragma once
#include "VertexBuffer.h"
#include <Vector3.h>
#include <vector>

class Mesh
{
public:
	friend class Model;

	Mesh(VertexFormat format, int usage);
	~Mesh();

	void setVertexData(const int vertexCount, const void* data);
	void setElementsData(const int vertexCount, const void* data);

private:
	int usage;
	int vertexCount;
	VertexFormat format;

	union {
		struct {
			GLuint vbo; //vertex buffer object
			GLuint ebo; //element buffer object
		};

		GLuint buffers[2];
	};
	
};