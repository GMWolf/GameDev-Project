#include "stdafx.h"
#include "Mesh.h"
#include "VBBuilder.h"
#include <iostream>

Mesh Mesh::Triangle(const glm::vec3 & p0, const glm::vec3 & p1, const glm::vec3 & p2, 
	const glm::vec2 & t0, const glm::vec2 & t1, const glm::vec2 & t2, 
	const glm::vec3 & n0, const glm::vec3 & n1, const glm::vec3 & n2)
{
	Mesh temp;
	temp.positions = { p0, p1, p2 };
	temp.UVs = { t0, t1, t2 };
	temp.normals = { n0, n1, n2 };
	temp.indices = { 0, 1, 2 };

	return temp;
}

Mesh Mesh::Quad(const glm::vec3 & p0, const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3,
	const glm::vec2 & t0, const glm::vec2 & t1, const glm::vec2 & t2, const glm::vec2 & t3,
	const glm::vec3 & n0, const glm::vec3 & n1, const glm::vec3 & n2, const glm::vec3 & n3)
{
	Mesh temp;
	temp.positions = { p0, p1, p2, p3 };
	temp.UVs = { t0, t1, t2, t3 };
	temp.normals = { n0, n1, n2, n3 };
	temp.indices = { 0,1,2,2,3,0 };

	return temp;
}

Mesh Mesh::Cube(glm::vec3 s)
{
	s /= 2;
	Mesh temp;
	
	//z-
	temp += Quad(glm::vec3(-s.x, -s.y, -s.z), glm::vec3(s.x, -s.y, -s.z), glm::vec3(s.x, s.y, -s.z), glm::vec3(-s.x, s.y, -s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1), glm::vec3(0, 0, -1));
	//z+
	temp += Quad(glm::vec3(-s.x, -s.y, s.z), glm::vec3(-s.x, s.y, s.z), glm::vec3(s.x, s.y, s.z), glm::vec3(s.x, -s.y, s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1));
	//x-
	temp += Quad(glm::vec3(-s.x, -s.y, -s.z), glm::vec3(-s.x, s.y, -s.z), glm::vec3(-s.x, s.y, s.z), glm::vec3(-s.x, -s.y, s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0));
	//x+
	temp += Quad(glm::vec3(s.x, -s.y, -s.z), glm::vec3(s.x, -s.y, s.z), glm::vec3(s.x, s.y, s.z), glm::vec3(s.x, s.y, -s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0));
	//y-
	temp += Quad(glm::vec3(-s.x, -s.y, -s.z), glm::vec3(-s.x, -s.y, s.z), glm::vec3(s.x, -s.y, s.z), glm::vec3(s.x, -s.y, -s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(0, -1, 0), glm::vec3(0, -1, 0), glm::vec3(0, -1, 0), glm::vec3(0, -1, 0));
	//y+
	temp += Quad(glm::vec3(-s.x, s.y, -s.z), glm::vec3(-s.x, s.y, s.z), glm::vec3(s.x, s.y, s.z), glm::vec3(s.x, s.y, -s.z),
		glm::vec2(0, 0), glm::vec2(1, 0), glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));


	return temp;
}



Mesh Mesh::operator+(const Mesh & rhs) const
{
	Mesh temp = *this;
	temp += rhs;
	return temp;
}

Mesh & Mesh::operator+=(const Mesh & rhs)
{
	const int iOffset = positions.size();

	positions.insert(positions.end(), rhs.positions.begin(), rhs.positions.end());
	UVs.insert(UVs.end(), rhs.UVs.begin(), rhs.UVs.end());
	normals.insert(normals.end(), rhs.normals.begin(), rhs.normals.end());

	
	for (int i = 0; i < rhs.indices.size(); i++) {
		indices.push_back(rhs.indices[i] + iOffset);
	}

	return *this;
}
