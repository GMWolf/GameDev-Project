#pragma once
#include <vector>
#include "Vector3.h"
#include <map>
#include <unordered_map>
#include <glm/detail/type_vec3.hpp>

//https://schneide.wordpress.com/2016/07/15/generating-an-icosphere-in-c/
class Icosphere
{
public:
	using index = unsigned int;
	struct Triangle
	{
		index vertex[3];
	};
	static void generate(int subdiv, std::vector<unsigned int>& elements, std::vector<glm::vec3>& vertices);

	
	using Lookup = std::map<std::pair<index, index>, index>;
	

	

private:
	

	static const float X; 
	static const float Z; 
	static const float N; 

	static const std::vector<glm::vec3> icoVertices;
	static const std::vector<Triangle> icoTriangles;

	static unsigned int vertexForEdge(Lookup& lookup, std::vector<glm::vec3>& vertices, index first, index second);
	static std::vector<Triangle> subdivide(std::vector<glm::vec3>& vertices, std::vector<Triangle> triangles);

	Icosphere();
	~Icosphere();
};

