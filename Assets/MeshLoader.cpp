#include "stdafx.h"
#include "MeshLoader.h"
#include <cstdio>
#include <iostream>

void AssetLoader<Mesh>::load(std::string fileName, Mesh& mesh)
{
	FILE * file;
	fopen_s(&file, fileName.c_str(), "r");
	if (file == nullptr) {
		std::cout << "Could not open file " << fileName;
		return;
	}

	std::vector<glm::vec3> obj_vertices;
	std::vector<glm::vec2> obj_uvs;
	std::vector<glm::vec3> obj_normals;

	std::vector<vertexData> vertices;
	std::vector<int> elements;

	while (true) {
		char lineHeader[256];
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF) {
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			obj_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			obj_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			obj_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			vertexData v0;
			vertexData v1;
			vertexData v2;

			fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v0.position, &v0.uv, &v0.normal,
				&v1.position, &v1.uv, &v1.normal,
				&v2.position, &v2.uv, &v2.normal);

			addVertexData(v0, vertices, elements);
			addVertexData(v1, vertices, elements);
			addVertexData(v2, vertices, elements);
		}
	}

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;


	for (int i = 0; i < vertices.size(); i++) {
		positions.push_back(obj_vertices[vertices[i].position - 1]);
		normals.push_back(obj_normals[vertices[i].normal - 1]);
		uvs.push_back(obj_uvs[vertices[i].uv - 1]);
	}

	/*
	mesh.positions = positions;
	mesh.normals = normals;
	mesh.UVs = uvs;
	mesh.indices = elements;*/
	mesh.positions.swap(positions);
	mesh.normals.swap(normals);
	mesh.UVs.swap(uvs);
	mesh.indices.swap(elements);
}

AssetLoader<Mesh>::vertexData::vertexData()
{
}

AssetLoader<Mesh>::vertexData::vertexData(int position, int uv, int normal): position(position), uv(uv), normal(normal)
{
}

bool AssetLoader<Mesh>::vertexData::operator==(const vertexData& rhs) const
{
	return position == (rhs.position) && (uv == rhs.uv) && (normal == rhs.normal);
}

void AssetLoader<Mesh>::addVertexData(vertexData & data, std::vector<vertexData>& vertices, std::vector<int>& elements)
{

	/*auto fv0 = std::find(vertices.begin(), vertices.end(), data);
	if (fv0 == vertices.end()) {
		elements.push_back(vertices.size());
		vertices.push_back(data);
	}
	else {
		elements.push_back(std::distance(vertices.begin(), fv0));
	}*/
	elements.push_back(vertices.size());
	vertices.push_back(data);
}
