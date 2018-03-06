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
	~Mesh();

	void update();
	void combine(Mesh& other);
	void draw();

	MeshData operator+(Mesh& rhs);


	VertexBuffer vertexBuffer;
	union {
		struct {
			std::vector<Vector3> positions;
			std::vector<Vector2> UVs;
			std::vector<Vector3> normals;
			std::vector<int> indices;
		};
		MeshData data;
	};



	static MeshData Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2,
		const Vector2& t0, const Vector2& t1, const Vector2& t2,
		const Vector3& n0, const Vector3& n1, const Vector3& n2);
	static MeshData Quad(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3,
		const Vector2& t0, const Vector2& t1, const Vector2& t2, const Vector2& t3,
		const Vector3& n0, const Vector3& n1, const Vector3& n2, const Vector3& n3);

	static MeshData Cube(Vector3 size);

	static const VertexFormat format;
	
	struct Attributes {
		static const VertexAttribute POSITION;
		static const VertexAttribute TEXTURE_COORDINATES;
		static const VertexAttribute COLOUR;
		static const VertexAttribute NORMAL;
	};

private:

	void combine_internal(Mesh& other);

	VertexArray vertexArray;
	
	int vertexCount;
};

