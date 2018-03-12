#include "stdafx.h"
#include "Icosphere.h"
#include <array>

const float Icosphere::X = .525731112119133606f;
const float Icosphere::Z = .850650808352039932f;
const float Icosphere::N = 0.f;

const std::vector<Vector3> Icosphere::icoVertices = {
	{ -X,N,Z },{ X,N,Z },{ -X,N,-Z },{ X,N,-Z },
	{ N,Z,X },{ N,Z,-X },{ N,-Z,X },{ N,-Z,-X },
	{ Z,X,N },{ -Z,X, N },{ Z,-X,N },{ -Z,-X, N }
};

const std::vector<Icosphere::Triangle> Icosphere::icoTriangles = {
	{ 0,4,1 },{ 0,9,4 },{ 9,5,4 },{ 4,5,8 },{ 4,8,1 },
	{ 8,10,1 },{ 8,3,10 },{ 5,3,8 },{ 5,2,3 },{ 2,7,3 },
	{ 7,10,3 },{ 7,6,10 },{ 7,11,6 },{ 11,0,6 },{ 0,1,6 },
	{ 6,1,10 },{ 9,0,11 },{ 9,11,2 },{ 9,2,5 },{ 7,2,11 }
};

void Icosphere::generate(int subdiv, std::vector<unsigned int>& elements, std::vector<Vector3>& vertices)
{
	vertices = icoVertices;
	std::vector<Triangle> triangles = icoTriangles;

	for(int i=0; i < subdiv; i++)
	{
		triangles = subdivide(vertices, triangles);
	}
	
	elements.clear();
	for(Triangle& t : triangles)
	{
		elements.push_back(t.vertex[0]);
		elements.push_back(t.vertex[1]);
		elements.push_back(t.vertex[2]);
	}
}

unsigned Icosphere::vertexForEdge(Lookup& lookup, std::vector<Vector3>& vertices, index first, index second)
{
	Lookup::key_type key(first, second);
	if (key.first > key.second)
		std::swap(key.first, key.second);

	auto inserted = lookup.insert({ key, vertices.size() });
	if (inserted.second)
	{
		auto& edge0 = vertices[first];
		auto& edge1 = vertices[second];
		auto point = (edge0 + edge1);
		point.Normalize();

		vertices.push_back(point);
	}

	return inserted.first->second;
}

std::vector<Icosphere::Triangle> Icosphere::subdivide(std::vector<Vector3>& vertices, std::vector<Triangle> triangles)
{
	Lookup lookup;
	std::vector<Triangle> result;
	for(auto&& each : triangles)
	{
		std::array<index, 3> mid;
		for(int edge = 0; edge < 3; ++edge)
		{
			mid[edge] = vertexForEdge(lookup, vertices, each.vertex[edge], each.vertex[(edge + 1) % 3]);
		}
		result.push_back({ each.vertex[0], mid[0], mid[2] });
		result.push_back({ each.vertex[1], mid[1], mid[0] });
		result.push_back({ each.vertex[2], mid[2], mid[1] });
		result.push_back({ mid[0], mid[1], mid[2] });
	}
	return result;
}

Icosphere::Icosphere()
{
}


Icosphere::~Icosphere()
{
}
