#pragma once
#include "ComponentMapper.h"
#include "Aspect.h"
#include <iostream>

namespace ECS {



	//CRTP class for components
	template<class T, int chunkSize>
	class Component{
	public:
		void load(const nlohmann::json& json);
		static ComponentMapper<T, chunkSize> componentMapper;
		static ComponentLoader* loader;
		static int componentId;
	};

	template <class T, int chunkSize>
	void Component<T, chunkSize>::load(const nlohmann::json& json)
	{
		std::cout << T::componentName << " load not implemented" << std::endl;
	}

	template<class T, int chunkSize>
	int Component<T, chunkSize>::componentId = -1;// = uniqueId;

	template<class T, int chunkSize>
	ComponentMapper<T, chunkSize> Component<T, chunkSize>::componentMapper;

	template<class T, int chunkSize>
	ComponentLoader* Component<T, chunkSize>::loader = nullptr;

#define COMPONENT(name, chunkSize) \
	template<class T> \
	struct _##name##_internal: public ECS::Component<T, chunkSize> \
	{static constexpr char componentName[] = #name;};\
	/*template<class T> const std::string _##name##_internal<T>::componentName = #name;*/\
	struct name : public _##name##_internal<name>
}