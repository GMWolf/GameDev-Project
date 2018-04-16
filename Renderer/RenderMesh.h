#pragma once
#pragma once
#include "VertexFormat.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Mesh.h"

class RenderMesh
{
public:
	RenderMesh();
	RenderMesh(const Mesh& data);
	~RenderMesh();

	void submit() const;

	static const wagl::VertexFormat format;
	struct Attributes {
		static const wagl::VertexAttribute POSITION;
		static const wagl::VertexAttribute TEXTURE_COORDINATES;
		static const wagl::VertexAttribute COLOUR;
		static const wagl::VertexAttribute NORMAL;
		static const wagl::VertexAttribute TANGENT;
		static const wagl::VertexAttribute BITANGENT;
	};

	void setData(const Mesh& data);
private:

	static void computeTangents(const Mesh& data, std::vector<glm::vec3>& tangents, std::vector<glm::vec3>& bitangents);

	wagl::VertexBuffer vb;
	wagl::VertexArray va;
	int elementCount;
};

