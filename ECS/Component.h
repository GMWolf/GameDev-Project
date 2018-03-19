#pragma once
#include "ComponentMapper.h"
#include "Aspect.h"
#include <iostream>

namespace detail
{
	inline int& getCounter()
	{
		static int result{ 0 };
		return result;
	}
}

inline int nextId()
{
	return detail::getCounter()++;
}

class ComponentId
{
public:
	ComponentId();

	int id;
};


//CRTP class for components
template<class T, int chunkSize>
class Component {
public:
	void load(const nlohmann::json& json);
	static const int componentId;
	static ComponentMapper<T, chunkSize> componentMapper;
};

template <class T, int chunkSize>
void Component<T, chunkSize>::load(const nlohmann::json& json)
{
	std::cout << T::componentName <<" load not implemented" << std::endl;
}

template<class T, int chunkSize>
const int Component<T, chunkSize>::componentId = nextId();

template<class T, int chunkSize>
ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

#define COMPONENT(name, chunkSize) \
	template<class T> \
	struct _##name##_internal: public Component<T, chunkSize> \
	{static const std::string componentName;};\
	template<class T> const std::string _##name##_internal<T>::componentName = #name; \
	struct name : public _##name##_internal<name>