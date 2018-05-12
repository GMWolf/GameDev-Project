#pragma once
#include "ComponentMapper.h"
#include "Aspect.h"
#include <iostream>

namespace ECS {
	int* getCompCounter();
	
	int nextId();

	struct UniqueId
	{
		UniqueId();
		int id;
		operator int() const
		{
			return id;
		}
	};

	//CRTP class for components
	template<class T, int chunkSize, int uniqueId>
	class Component{
	public:
		void load(const nlohmann::json& json);
		static ComponentMapper<T, chunkSize> componentMapper;
		static ComponentLoader* loader;
		const static int componentId;
	};

	template <class T, int chunkSize, int uniqueId>
	void Component<T, chunkSize, uniqueId>::load(const nlohmann::json& json)
	{
		std::cout << T::componentName << " load not implemented" << std::endl;
	}

	template<class T, int chunkSize, int uniqueId>
	const int Component<T, chunkSize, uniqueId>::componentId = uniqueId;

	template<class T, int chunkSize, int uniqueId>
	ComponentMapper<T, chunkSize> Component<T, chunkSize, uniqueId>::componentMapper;

	template<class T, int chunkSize, int uniqueId>
	ComponentLoader* Component<T, chunkSize, uniqueId>::loader = nullptr;

#define COMPONENT(name, chunkSize, uniqueId) \
	template<class T> \
	struct _##name##_internal: public ECS::Component<T, chunkSize, uniqueId> \
	{static constexpr char componentName[] = #name;};\
	/*template<class T> const std::string _##name##_internal<T>::componentName = #name;*/\
	struct name : public _##name##_internal<name>
}