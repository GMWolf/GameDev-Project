#pragma once
#include "ComponentMapper.h"
#include "Aspect.h"
#include <vector>
class Components {
public:
	static int next_component_id;

};

//CRTP class for components
template<class T, int chunkSize>
class Component {
public:

	static const int componentId;
	static ComponentMapper<T, chunkSize> componentMapper;
	static const Aspect componentAspect;
};

template<class T, int chunkSize>
const int Component<T, chunkSize>::componentId = Components::next_component_id++;

template<class T, int chunkSize>
ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

template<class T, int chunkSize>
const Aspect Component<T, chunkSize>::componentAspect = Aspect::compAspect<T>();

#define COMPONENT(name, chunkSize) \
	struct name : public Component<name, chunkSize>