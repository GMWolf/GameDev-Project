#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() : vertexBuffer(format, GL_STATIC_DRAW), vertexArray(vertexBuffer)
{
}

Mesh::Mesh(const MeshData& data) : vertexBuffer(format, GL_STATIC_DRAW), vertexArray(vertexBuffer), data(data)
{
	update();
}

Mesh::~Mesh()
{
}

void Mesh::update()
{
	VBBuilder builder(format);
	builder.set(Attributes::POSITION, positions);
	builder.set(Attributes::TEXTURE_COORDINATES, UVs);
	builder.set(Attributes::NORMAL, normals);
	builder.setElems(indices);
	builder.update(vertexBuffer);
}

void Mesh::combine(Mesh & other)
{
	combine_internal(other);
	update();
}

MeshData Mesh::operator+(Mesh & rhs)
{
	return data + rhs.data;
}




MeshData Mesh::Triangle(const Vector3 & p0, const Vector3 & p1, const Vector3 & p2, 
	const Vector2 & t0, const Vector2 & t1, const Vector2 & t2, 
	const Vector3 & n0, const Vector3 & n1, const Vector3 & n2)
{
	MeshData temp;
	temp.positions = { p0, p1, p2 };
	temp.UVs = { t0, t1, t2 };
	temp.normals = { n0, n1, n2 };
	temp.indices = { 0, 1, 2 };

	return temp;
}

MeshData Mesh::Quad(const Vector3 & p0, const Vector3 & p1, const Vector3 & p2, const Vector3 & p3,
	const Vector2 & t0, const Vector2 & t1, const Vector2 & t2, const Vector2 & t3,
	const Vector3 & n0, const Vector3 & n1, const Vector3 & n2, const Vector3 & n3)
{
	MeshData temp;
	temp.positions = { p0, p1, p2, p3 };
	temp.UVs = { t0, t1, t2, t3 };
	temp.normals = { n0, n1, n2, n3 };
	temp.indices = { 0,1,2,2,3,0 };

	return temp;
}

MeshData Mesh::Cube(Vector3 s)
{
	s /= 2;
	MeshData temp;
	
	//z-
	temp += Quad(Vector3(-s.x, -s.y, -s.z), Vector3(s.x, -s.y, -s.z), Vector3(s.x, s.y, -s.z), Vector3(-s.x, s.y, -s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, 0, -1), Vector3(0, 0, -1), Vector3(0, 0, -1), Vector3(0, 0, -1));
	//z+
	temp += Quad(Vector3(-s.x, -s.y, s.z), Vector3(-s.x, s.y, s.z), Vector3(s.x, s.y, s.z), Vector3(s.x, -s.y, s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1), Vector3(0, 0, 1));
	//x-
	temp += Quad(Vector3(-s.x, -s.y, -s.z), Vector3(-s.x, s.y, -s.z), Vector3(-s.x, s.y, s.z), Vector3(-s.x, -s.y, s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(-1, 0, 0), Vector3(-1, 0, 0), Vector3(-1, 0, 0), Vector3(-1, 0, 0));
	//x+
	temp += Quad(Vector3(s.x, -s.y, -s.z), Vector3(s.x, -s.y, s.z), Vector3(s.x, s.y, s.z), Vector3(s.x, s.y, -s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(1, 0, 0), Vector3(1, 0, 0), Vector3(1, 0, 0), Vector3(1, 0, 0));
	//y-
	temp += Quad(Vector3(-s.x, -s.y, -s.z), Vector3(-s.x, -s.y, s.z), Vector3(s.x, -s.y, s.z), Vector3(s.x, -s.y, -s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, -1, 0), Vector3(0, -1, 0), Vector3(0, -1, 0), Vector3(0, -1, 0));
	//y+
	temp += Quad(Vector3(-s.x, s.y, -s.z), Vector3(-s.x, s.y, s.z), Vector3(s.x, s.y, s.z), Vector3(s.x, s.y, -s.z),
		Vector2(0, 0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, 1, 0), Vector3(0, 1, 0), Vector3(0, 1, 0), Vector3(0, 1, 0));


	return temp;
}

void Mesh::combine_internal(Mesh & other)
{
	data += other.data;
}

void Mesh::draw()
{
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

const VertexAttribute Mesh::Attributes::POSITION = { GL_FLOAT, 3, "position" };
const VertexAttribute Mesh::Attributes::TEXTURE_COORDINATES = { GL_FLOAT, 2, "texCoord" };
const VertexAttribute Mesh::Attributes::COLOUR = { GL_FLOAT, 4, "colour" };
const VertexAttribute Mesh::Attributes::NORMAL = { GL_FLOAT, 3, "normal" };

const VertexFormat Mesh::format = {
	Mesh::Attributes::POSITION,
	Mesh::Attributes::TEXTURE_COORDINATES,
	Mesh::Attributes::NORMAL
};



MeshData MeshData::operator+(const MeshData & rhs) const
{
	MeshData temp = *this;
	temp += rhs;
	return temp;
}

MeshData & MeshData::operator+=(const MeshData & rhs)
{
	int iOffset = positions.size();

	positions.insert(positions.end(), rhs.positions.begin(), rhs.positions.end());
	UVs.insert(UVs.end(), rhs.UVs.begin(), rhs.UVs.end());
	normals.insert(normals.end(), rhs.normals.begin(), rhs.normals.end());

	
	for (int i = 0; i < rhs.indices.size(); i++) {
		indices.push_back(rhs.indices[i] + iOffset);
	}

	return *this;
}
