#pragma once
#include "ComponentMapper.h"
#include "Aspect.h"
#include <iostream>

class Components {
public:
	static int next_component_id;
};


//CRTP class for components
template<class T, int chunkSize>
class Component {
public:
	void load(const nlohmann::json& json);
	static const int componentId;
	static ComponentMapper<T, chunkSize> componentMapper;
	static const Aspect componentAspect;
};

template <class T, int chunkSize>
void Component<T, chunkSize>::load(const nlohmann::json& json)
{
	std::cout << T::componentName <<" load not implemented" << std::endl;
}


template<class T, int chunkSize>
const int Component<T, chunkSize>::componentId = Components::next_component_id++;

template<class T, int chunkSize>
ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

template<class T, int chunkSize>
const Aspect Component<T, chunkSize>::componentAspect = Aspect::compAspect<T>();

#define COMPONENT(name, chunkSize) \
	template<class T> \
	struct _##name##_internal: public Component<T, chunkSize> \
	{static const std::string componentName;};\
	template<class T> const std::string _##name##_internal<T>::componentName = #name; \
	struct name : public _##name##_internal<name>