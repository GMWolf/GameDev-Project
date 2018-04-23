#pragma once
#include <vector>
#include <glm/detail/type_vec3.hpp>


struct Mesh {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	Mesh operator+(const Mesh& rhs) const;
	Mesh& operator+=(const Mesh& rhs);

	static Mesh Triangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2,
		const glm::vec2& t0, const glm::vec2& t1, const glm::vec2& t2,
		const glm::vec3& n0, const glm::vec3& n1, const glm::vec3& n2);
	static Mesh Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
		const glm::vec2& t0, const glm::vec2& t1, const glm::vec2& t2, const glm::vec2& t3,
		const glm::vec3& n0, const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3);

	static Mesh Cube(glm::vec3 size);
};
