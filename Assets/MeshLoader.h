#pragma once
#include <string>
#include <vector>
#include "Mesh.h"
#include "AssetLoader.h"

template<>
class AssetLoader<Mesh>
{
public:

	void load(std::string file, Mesh& location);

private:

	struct vertexData {
		vertexData();

		vertexData(int position, int uv, int normal);;

		bool operator==(const vertexData& rhs) const;;

		

		int position;
		int uv;
		int normal;
	};

	static void addVertexData(vertexData& data, std::vector<vertexData>& vertices, std::vector<int>& elements);
};

