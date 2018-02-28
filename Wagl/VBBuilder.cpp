#include "VBBuilder.h"

VBBuilder::VBBuilder(VertexFormat format) : format(format), vertexCount(0)
{

}

VBBuilder::~VBBuilder()
{
	for (auto ptr : attribData) {
		delete[] ptr.second;
	}
}

void VBBuilder::setElems(std::vector<int> elems)
{
	elements = elems;
}

void VBBuilder::setElems(std::initializer_list<int> elements)
{
	std::vector<int> v(elements);
	setElems(v);
}

VertexBuffer * VBBuilder::build()
{
	VertexBuffer* mesh = new VertexBuffer(format, GL_STATIC_DRAW);

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
