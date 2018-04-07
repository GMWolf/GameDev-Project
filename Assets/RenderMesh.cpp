#include "stdafx.h"
#include "RenderMesh.h"
#include "VBBuilder.h"


const wagl::VertexAttribute RenderMesh::Attributes::POSITION = { GL_FLOAT, 3, "position" };
const wagl::VertexAttribute RenderMesh::Attributes::TEXTURE_COORDINATES = { GL_FLOAT, 2, "texCoord" };
const wagl::VertexAttribute RenderMesh::Attributes::COLOUR = { GL_FLOAT, 4, "colour" };
const wagl::VertexAttribute RenderMesh::Attributes::NORMAL = { GL_FLOAT, 3, "normal" };
const wagl::VertexAttribute RenderMesh::Attributes::TANGENT = { GL_FLOAT, 3, "tangent" };
const wagl::VertexAttribute RenderMesh::Attributes::BITANGENT = { GL_FLOAT, 3, "bitangent" };

const wagl::VertexFormat RenderMesh::format = {
	Attributes::POSITION,
	Attributes::TEXTURE_COORDINATES,
	Attributes::NORMAL,
	Attributes::TANGENT,
	Attributes::BITANGENT
};

RenderMesh::RenderMesh() : vb(format, GL_STATIC_DRAW), va(vb), elementCount(0)
{
}


RenderMesh::RenderMesh(const Mesh& data) :
	vb(format, GL_STATIC_DRAW), va(vb)
{
	setData(data);
}


RenderMesh::~RenderMesh()
{
}

void RenderMesh::submit() const
{
	va.bind();
	glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)0);
	wagl::VertexArray::unbind();
}

void RenderMesh::setData(const Mesh& data)
{
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> bitangents;
	computeTangents(data, tangents, bitangents);

	wagl::VBBuilder builder(format);
	builder.set(Attributes::POSITION, data.positions);
	builder.set(Attributes::TEXTURE_COORDINATES, data.UVs);
	builder.set(Attributes::NORMAL, data.normals);
	builder.set(Attributes::TANGENT, tangents);
	builder.set(Attributes::BITANGENT, bitangents);
	builder.setElems(data.indices);
	builder.update(vb);

	elementCount = data.indices.size();
}

void RenderMesh::computeTangents(const Mesh& data, std::vector<glm::vec3>& tangents, std::vector<glm::vec3>& bitangents)
{
	tangents.resize(data.positions.size(), glm::vec3(0, 0, 0));
	bitangents.resize(data.positions.size(), glm::vec3(0, 0, 0));
	//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/
	for (int i = 0; i < data.indices.size(); i += 3)
	{
		const int i0 = data.indices[i];
		const int i1 = data.indices[i + 1];
		const int i2 = data.indices[i + 2];


		const glm::vec3& v0 = data.positions[i0];
		const glm::vec3& v1 = data.positions[i1];
		const glm::vec3& v2 = data.positions[i2];

		const glm::vec2& uv0 = data.UVs[i0];
		const glm::vec2& uv1 = data.UVs[i1];
		const glm::vec2& uv2 = data.UVs[i2];

		const glm::vec3 deltaPos1 = v1 - v0;
		const glm::vec3 deltaPos2 = v2 - v0;

		const glm::vec2 deltaUV1 = uv1 - uv0;
		const glm::vec2 deltaUV2 = uv2 - uv0;

		const float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
		const glm::vec3 tangent = ((deltaPos1 * deltaUV2.y) - (deltaPos2 * deltaUV1.y)) * r;
		const glm::vec3 bitangent = ((deltaPos2 * deltaUV1.x) - (deltaPos1 * deltaUV2.x)) * r;

		if (glm::dot(glm::cross(data.normals[i0], tangent), bitangent) < 0.0f)
		{
			tangents[i0] += -tangent;
		}
		else
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
