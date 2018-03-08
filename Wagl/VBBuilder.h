#pragma once
#include "VertexFormat.h"
#include <string>
#include <vector>
#include <map>
#include <assert.h>
#include "VertexBuffer.h"
#include <initializer_list>
class VBBuilder {
public:

	VBBuilder(const VertexFormat& format);
	~VBBuilder();

	template<class T>
	void set(std::string alias, std::vector<T>& data);

	template<class T>
	void set(VertexAttribute attribute, std::vector<T>& data);

	template<class T>
	void set(VertexAttribute attribute, std::initializer_list<T> data);

	template<class T>
	void set(int ai, std::vector<T>& data);

	void setElems(std::vector<int>& elements);
	void setElems(std::initializer_list<int> elements);

	VertexBuffer* build();
	
	void update(VertexBuffer& vb);

private:
	const VertexFormat& format;

	std::map<int, char*> attribData;
	std::vector<int> elements;
	int vertexCount;
};

template<class T>
inline void VBBuilder::set(std::string alias, std::vector<T>& data)
{
	bool found;
	const VertexAttribute& va = format.findAttribute(alias, found);
	if (found) {
		set(va, data);
	}
}

template<class T>
inline void VBBuilder::set(VertexAttribute attribute, std::vector<T>& data)
{
	assert(attribute.size() == sizeof(T));

	const int ai = format.getAttributeNumber(attribute);

	set(ai, data);
}

template<class T>
inline void VBBuilder::set(VertexAttribute attribute, std::initializer_list<T> data)
{
	std::vector<T> d(data);
	set(attribute, d);
}

template <class T>
void VBBuilder::set(int ai, std::vector<T>& data)
{
	VertexAttribute attribute = format.attributes[ai];

	attribData[ai] = (char*) data.data();

	vertexCount = data.size();
}
