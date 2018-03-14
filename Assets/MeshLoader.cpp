#include "stdafx.h"
#include "meshLoader.h"
#include <cstdio>
#include <iostream>

Mesh * MeshLoader::LoadObj(std::string fileName)
{
	FILE * file;
	fopen_s(&file, fileName.c_str(), "r");
	if (file == nullptr) {
		std::cout << "Could not open file " << fileName;
		return nullptr;
	}

	std::vector<Vector3> obj_vertices;
	std::vector<Vector2> obj_uvs;
	std::vector<Vector3> obj_normals;

	std::vector<vertexData> vertices;
	std::vector<int> elements;

	while (true) {
		char lineHeader[256];
		int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));
		if (res == EOF) {
			break;
		}

		if (strcmp(lineHeader, "v") == 0) {
			Vector3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			obj_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			Vector2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			obj_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			obj_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			vertexData v0, v1, v2;

			fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&v0.position, &v0.uv, &v0.normal,
				&v1.position, &v1.uv, &v1.normal,
				&v2.position, &v2.uv, &v2.normal);

			addVertexData(v0, vertices, elements);
			addVertexData(v1, vertices, elements);
			addVertexData(v2, vertices, elements);
		}
	}

	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<Vector2> uvs;

	for (int i = 0; i < vertices.size(); i++) {
		positions.push_back(obj_vertices[vertices[i].position - 1]);
		normals.push_back(obj_normals[vertices[i].normal - 1]);
		uvs.push_back(obj_uvs[vertices[i].uv - 1]);
	}

	Mesh * mesh = new Mesh();
	mesh->positions = positions;
	mesh->normals = normals;
	mesh->UVs = uvs;
	mesh->indices = elements;

	mesh->update();

	return mesh;
}

MeshLoader::vertexData::vertexData()
{
}

MeshLoader::vertexData::vertexData(int position, int uv, int normal): position(position), uv(uv), normal(normal)
{
}

bool MeshLoader::vertexData::operator==(const vertexData& rhs) const
{
	return position == (rhs.position) && (uv == rhs.uv) && (normal == rhs.normal);
}

void MeshLoader::addVertexData(vertexData & data, std::vector<vertexData>& vertices, std::vector<int>& elements)
{
	/*auto fv0 = std::find(vertices.begin(), vertices.end(), data);
	if (fv0 == vertices.end()) {*/
		elements.push_back(vertices.size());
		vertices.push_back(data);
	/*}
	else {
		elements.push_back(std::distance(vertices.begin(), fv0));
	}*/
}

MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
}

