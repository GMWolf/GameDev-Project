#include "MeshBuilder.h"

MeshBuilder::MeshBuilder(VertexFormat format) : format(format), vertexCount(0)
{

}

MeshBuilder::~MeshBuilder()
{
	for (auto ptr : attribData) {
		delete[] ptr.second;
	}
}

void MeshBuilder::setElems(std::vector<int> elems)
{
	elements = elems;
}

void MeshBuilder::setElems(std::initializer_list<int> elements)
{
	std::vector<int> v(elements);
	setElems(v);
}

Mesh * MeshBuilder::build()
{
	Mesh* mesh = new Mesh(format, GL_STATIC_DRAW);

	char* vertData = new char[format.getStride() * vertexCount];

	for (int atNum = 0; atNum < format.attributes.size(); atNum++) {
		for (int i = 0; i < vertexCount; i++) {

			VertexAttribute attribute = format.attributes[atNum];

			char* ad = (char*)attribData[atNum]; //attribute data

			char* vad = ad + (attribute.size() * i); //vertex attrib data

			char* to = vertData + (format.getStride() * i) + format.getOffset(atNum);

			memcpy(to, vad, attribute.size());

		}
	}


	mesh->setVertexData(vertexCount, vertData);
	mesh->setElementsData(elements.size(), elements.data());

	return mesh;

	delete vertData;
}
