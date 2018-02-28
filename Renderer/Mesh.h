#pragma once
#include <VertexBuffer.h>
#include <VertexFormat.h>
#include <VBBuilder.h>
#include <VertexArray.h>
#include <vector>
#include <Vector3.h>
#include <Vector2.h>
class Mesh
{
public:
	Mesh();
	~Mesh();

	void update();
	void combine(Mesh& other);

	std::vector<Vector3> positions;
	std::vector<Vector2> UVs;
	std::vector<Vector3> normals;
	std::vector<int> indices;

	void draw();

	static const VertexFormat format;

	static struct Attributes {
		static const VertexAttribute POSITION;
		static const VertexAttribute TEXTURE_COORDINATES;
		static const VertexAttribute COLOUR;
		static const VertexAttribute NORMAL;
	};

	VertexBuffer vertexBuffer;
private:
	VertexArray vertexArray;
	
	int vertexCount;
};

