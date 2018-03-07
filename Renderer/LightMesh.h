#pragma once
#include <VertexArray.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <vector>
#include <Vector3.h>

class LightMesh
{
public:
	LightMesh();
	~LightMesh();

	void draw();

	void addLight(const Vector3& position, const Vector3& colour, float radius);
	void clear();

private:
	std::vector<Vector3> positions{};
	std::vector<Vector3> colours{};
	std::vector<float> radii{};
	std::vector<int> elements{};

	
	VertexBuffer vb;
	VertexArray va;

	int vertexCount;

	void updateBuffers();

	bool dirty;

	static const VertexFormat format;
};

