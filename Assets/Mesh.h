#pragma once
#include <VertexBuffer.h>
#include <VertexFormat.h>
#include <VertexArray.h>
#include <vector>
#include <Vector3.h>
#include <Vector2.h>


struct MeshData {
	std::vector<Vector3> positions;
	std::vector<Vector2> UVs;
	std::vector<Vector3> normals;
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
		

	static MeshData Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2,
		const Vector2& t0, const Vector2& t1, const Vector2& t2,
		const Vector3& n0, const Vector3& n1, const Vector3& n2);
	static MeshData Quad(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,
		const Vector2& t0, const Vector2& t1, const Vector2& t2, const Vector2& t3,
		const Vector3& n0, const Vector3& n1, const Vector3& n2, const Vector3& n3);

	static MeshData Cube(Vector3 size);

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

	std::vector<Vector3> tangents;
	std::vector<Vector3> bitangents;

	void computeTangents();

	void combine_internal(Mesh& other);

	wagl::VertexArray vertexArray;
};

