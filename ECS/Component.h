#pragma once
#include "ComponentMapper.h"



//CRTP class for components
template<class T, int chunkSize>
class Component {
public:
	static ComponentMapper<T, chunkSize> componentMapper;
};

template<class T, int chunkSize>
ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

#define COMPONENT(name, chunkSize) \
	struct name : public Component<name, chunkSize>