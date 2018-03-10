#include "VBBuilder.h"

wagl::VBBuilder::VBBuilder(const VertexFormat& format) : format(format), vertexCount(0)
{
}

wagl::VBBuilder::~VBBuilder()
{
}

void wagl::VBBuilder::setElems(std::vector<int>& elems)
{
	elements = elems;
}

void wagl::VBBuilder::setElems(std::initializer_list<int> elements)
{
	std::vector<int> v(elements);
	setElems(v);
}

wagl::VertexBuffer * wagl::VBBuilder::build()
{
	VertexBuffer* vb = new VertexBuffer(format, GL_STATIC_DRAW);

	update(*vb);

	return vb;
}

void wagl::VBBuilder::update(VertexBuffer & vb)
{
	char* vertData = new char[format.getStride() * vertexCount];

	for (unsigned int atNum = 0; atNum < format.attributes.size(); atNum++) {
		VertexAttribute attribute = format.attributes[atNum];
		char* ad = attribData[atNum]; //attribute data
		for (int i = 0; i < vertexCount; i++) {

			char* vad = ad + (attribute.size() * i); //vertex attrib data

			char* to = vertData + (format.getStride() * i) + format.getOffset(atNum);

			memcpy(to, vad, attribute.size());

		}
	}


	vb.setVertexData(vertexCount, vertData);
	vb.setElementsData(elements.size(), elements.data());


	delete[] vertData;
}
