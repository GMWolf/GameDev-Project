#pragma once
#include <HashedArrayTree.h>
#include <vector>
#include <utility>
#include <unordered_map>
#include <json.hpp>
#include "Aspect.h"
#include "ComponentLoader.h"

namespace ECS {

	class baseComponentMapper
	{
	public:
		virtual ~baseComponentMapper() = default;
		virtual void v_erase(int componentid) = 0;
		virtual void put(int id, nlohmann::json json) = 0;
		const virtual Aspect getAspect() = 0;
		virtual int getId() = 0;

		//Construct On First Use (static init order fiasco)
		static std::vector<baseComponentMapper*> * mappers();
		static std::unordered_map<std::string, baseComponentMapper*> * mappersByName();

		
	};

	template<class T, int chunkSize = 64>
	class ComponentMapper : public baseComponentMapper
	{
	public:
		ComponentMapper();
		virtual ~ComponentMapper();

		T& get(int componentId);

		template<class... Args>
		T& emplace(int componentId, Args && ...args);

		template<class... Args>
		T& put(int componentId, T& component);

		void put(int id, nlohmann::json json);

		void erase(int componentId);
	private:
		//Ensure erase is always called statically.
		//Only virtual when called from base
		//Compiler would probably take care of it be eh.
		void v_erase(int c) override {
			erase(c);
		}

	public:
		const Aspect getAspect() override;
		int getId() override;
	private:
		HashedArrayTree<chunkSize, T> components;
	};


	template<class T, int chunkSize>
	inline ComponentMapper<T, chunkSize>::ComponentMapper()
	{
		mappers()->at(T::componentId) = this;
		std::string name(T::componentName);
		//mappersByName()->at(name) = this;
		//std::cout << name << " inserted" << std::endl;
		mappersByName()->insert({ name, this });
	}

	template<class T, int chunkSize>
	inline ComponentMapper<T, chunkSize>::~ComponentMapper()
	{
	}

	template<class T, int chunkSize>
	inline T & ComponentMapper<T, chunkSize>::get(int componentId)
	{
		return components.at(componentId);
	}

	template<class T, int chunkSize>
	inline void ComponentMapper<T, chunkSize>::erase(int componentId)
	{
		components.erase(componentId);
	}

	template <class T, int chunkSize>
	const Aspect ComponentMapper<T, chunkSize>::getAspect()
	{
		return Aspect(1 << T::componentId);
	}

	template <class T, int chunkSize>
	int ComponentMapper<T, chunkSize>::getId()
	{
		return T::componentId;
	}

	template<class T, int chunkSize>
	template<class ...Args>
	inline T & ComponentMapper<T, chunkSize>::emplace(int componentId, Args && ...args)
	{
		components.put(componentId, std::forward<Args>(args)...);
		return components.at(componentId);
	}

	template<class T, int chunkSize>
	template<class ...Args>
	inline T & ComponentMapper<T, chunkSize>::put(int componentId, T & component)
	{
		components.put(componentId, component);
		return component;
	}

	template <class T, int chunkSize>
	void ComponentMapper<T, chunkSize>::put(int id, nlohmann::json json)
	{
		T comp;
		T::loader->load(json, &comp);
		//comp.load(json);
		put(id, comp);
	}
}