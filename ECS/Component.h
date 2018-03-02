#pragma once
#include "ComponentMapper.h"

int __next_component_id = 0;

//CRTP class for components
template<class T, int chunkSize>
class Component {
public:
	static ComponentMapper<T, chunkSize> componentMapper;

	static const int componentId;
};

template<class T, int chunkSize>
const int Component<T, chunkSize>::componentId = __next_component_id++;

template<class T, int chunkSize>
ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

#define COMPONENT(name, chunkSize) \
	struct name : public Component<name, chunkSize>