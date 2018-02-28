#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh() : vertexBuffer(format, GL_STATIC_DRAW), vertexArray(vertexBuffer)
{
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
	positions.insert(positions.end(), other.positions.begin(), other.positions.end());
	UVs.insert(UVs.end(), other.UVs.begin(), other.UVs.end());
	normals.insert(normals.end(), other.normals.begin(), other.normals.end());
	indices.insert(indices.end(), other.indices.begin(), other.indices.end());
	update();
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