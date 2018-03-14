#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
class MeshLoader
{
public:
	static Mesh* LoadObj(std::string file);

private:

	struct vertexData {
		vertexData();;

		vertexData(int position, int uv, int normal);;

		bool operator==(const vertexData& rhs) const;;

		

		int position;
		int uv;
		int normal;
	};

	static void addVertexData(vertexData& data, std::vector<vertexData>& vertices, std::vector<int>& elements);

	MeshLoader();
	~MeshLoader();
};

