#pragma once
#include <VertexBuffer.h>
#include <VertexFormat.h>
#include <VertexArray.h>
#include <vector>


struct MeshData {
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> normals;
	std::vector<int> indices;

	MeshData operator+(const MeshData& rhs) const;
	MeshData& operator+=(const MeshData& rhs);
};

class Mesh
{
public:
	Mesh();
	Mesh(const MeshData& data);
	Mesh(const Mesh& mesh);
	~Mesh();

	void update();
	void combine(Mesh& other);
	void draw();

	MeshData operator+(Mesh& rhs);

	Mesh& operator=(Mesh const & rhs);

	wagl::VertexBuffer vertexBuffer;

	MeshData data;
		

	static MeshData Triangle(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2,
		const glm::vec2& t0, const glm::vec2& t1, const glm::vec2& t2,
		const glm::vec3& n0, const glm::vec3& n1, const glm::vec3& n2);
	static MeshData Quad(const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3,
		const glm::vec2& t0, const glm::vec2& t1, const glm::vec2& t2, const glm::vec2& t3,
		const glm::vec3& n0, const glm::vec3& n1, const glm::vec3& n2, const glm::vec3& n3);

	static MeshData Cube(glm::vec3 size);

	static const wagl::VertexFormat format;
	
	struct Attributes {
		static const wagl::VertexAttribute POSITION;
		static const wagl::VertexAttribute TEXTURE_COORDINATES;
		static const wagl::VertexAttribute COLOUR;
		static const wagl::VertexAttribute NORMAL;
		static const wagl::VertexAttribute TANGENT;
		static const wagl::VertexAttribute BITANGENT;
	};

private:

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;

	void computeTangents();

	void combine_internal(Mesh& other);

	wagl::VertexArray vertexArray;
};

