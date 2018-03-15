#pragma once
#include <string>
#include <vector>
#include "AssetLoader.h"
#include "Mesh.h"

class AssetLoader<Mesh>
{
public:
	AssetLoader(Assets& assets);

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

	void addVertexData(vertexData& data, std::vector<vertexData>& vertices, std::vector<int>& elements);

	Assets& assets;
};

