#include "stdafx.h"
#include "Mesh.h"
#include "VBBuilder.h"
#include <iostream>

Mesh::Mesh() : vertexBuffer(format, GL_STATIC_DRAW), vertexArray(vertexBuffer)
{
	std::cout << "Mesh constructor!" << std::endl;
}

Mesh::Mesh(const MeshData& data) : vertexBuffer(format, GL_STATIC_DRAW), vertexArray(vertexBuffer), data(data)
{
	update();
}

Mesh::Mesh(const Mesh & mesh) : Mesh(mesh.data)
{

}



Mesh::~Mesh()
{
}

void Mesh::update()
{
	computeTangents();

	wagl::VBBuilder builder(format);
	builder.set(Attributes::POSITION, data.positions);
	builder.set(Attributes::TEXTURE_COORDINATES, data.UVs);
	builder.set(Attributes::NORMAL, data.normals);
	builder.set(Attributes::TANGENT, tangents);
	builder.set(Attributes::BITANGENT, bitangents);
	builder.setElems(data.indices);
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

Mesh & Mesh::operator=(Mesh const & rhs)
{
	data = rhs.data;
	update();
	return *this;
}

MeshData Mesh::Triangle(const glm::vec3 & p0, const glm::vec3 & p1, const glm::vec3 & p2, 
	const glm::vec2 & t0, const glm::vec2 & t1, const glm::vec2 & t2, 
	const glm::vec3 & n0, const glm::vec3 & n1, const glm::vec3 & n2)
{
	MeshData temp;
	temp.positions = { p0, p1, p2 };
	temp.UVs = { t0, t1, t2 };
	temp.normals = { n0, n1, n2 };
	temp.indices = { 0, 1, 2 };

	return temp;
}

MeshData Mesh::Quad(const glm::vec3 & p0, const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3,
	const glm::vec2 & t0, const glm::vec2 & t1, const glm::vec2 & t2, const glm::vec2 & t3,
	const glm::vec3 & n0, const glm::vec3 & n1, const glm::vec3 & n2, const glm::vec3 & n3)
{
	MeshData temp;
	temp.positions = { p0, p1, p2, p3 };
	temp.UVs = { t0, t1, t2, t3 };
	temp.normals = { n0, n1, n2, n3 };
	temp.indices = { 0,1,2,2,3,0 };

	return temp;
}

MeshData Mesh::Cube(glm::vec3 s)
{
	s /= 2;
	MeshData temp;
	
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

void Mesh::computeTangents()
{
	tangents.clear();
	bitangents.clear();
	tangents.resize(data.positions.size(), glm::vec3(0, 0, 0));
	bitangents.resize(data.positions.size(), glm::vec3(0, 0, 0));
	//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	for(int i = 0; i < data.indices.size(); i+=3)
	{
		int i0 = data.indices[i];
		int i1 = data.indices[i + 1];
		int i2 = data.indices[i + 2];


		glm::vec3& v0 = data.positions[i0];
		glm::vec3& v1 = data.positions[i1];
		glm::vec3& v2 = data.positions[i2];

		glm::vec2& uv0 = data.UVs[i0];
		glm::vec2& uv1 = data.UVs[i1];
		glm::vec2& uv2 = data.UVs[i2];

		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
		glm::vec3 tangent = ((deltaPos1 * deltaUV2.y) - (deltaPos2 * deltaUV1.y)) * r;
		glm::vec3 bitangent = ((deltaPos2 * deltaUV1.x) - (deltaPos1 * deltaUV2.x)) * r;

		if (glm::dot(glm::cross(data.normals[i0], tangent), bitangent) < 0.0f)
		{
			tangents[i0] += -tangent;
		} else
		{
			tangents[i0] += tangent;
		}

		if (glm::dot(glm::cross(data.normals[i1], tangent), bitangent) < 0.0f)
		{
			tangents[i1] += -tangent;
		}
		else
		{
			tangents[i1] += tangent;
		}

		if (glm::dot(glm::cross(data.normals[i2], tangent), bitangent) < 0.0f)
		{
			tangents[i2] += -tangent;
		}
		else
		{
			tangents[i2] += tangent;
		}

		bitangents[i0] += bitangent;
		bitangents[i1] += bitangent;
		bitangents[i2] += bitangent;
	}
}

void Mesh::combine_internal(Mesh & other)
{
	data += other.data;
}

void Mesh::draw()
{
	vertexArray.bind();
	glDrawElements(GL_TRIANGLES, data.indices.size(), GL_UNSIGNED_INT, (void*)0);
	wagl::VertexArray::unbind();
}

const wagl::VertexAttribute Mesh::Attributes::POSITION = { GL_FLOAT, 3, "position" };
const wagl::VertexAttribute Mesh::Attributes::TEXTURE_COORDINATES = { GL_FLOAT, 2, "texCoord" };
const wagl::VertexAttribute Mesh::Attributes::COLOUR = { GL_FLOAT, 4, "colour" };
const wagl::VertexAttribute Mesh::Attributes::NORMAL = { GL_FLOAT, 3, "normal" };
const wagl::VertexAttribute Mesh::Attributes::TANGENT = { GL_FLOAT, 3, "tangent" };
const wagl::VertexAttribute Mesh::Attributes::BITANGENT = { GL_FLOAT, 3, "bitangent" };

const wagl::VertexFormat Mesh::format = {
	Attributes::POSITION,
	Attributes::TEXTURE_COORDINATES,
	Attributes::NORMAL,
	Attributes::TANGENT,
	Attributes::BITANGENT
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
