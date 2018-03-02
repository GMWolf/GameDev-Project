#pragma once
#include <HashedArrayTree.h>
#include <utility>

int __next_component_id = 0;

template<class T, int chunkSize = 64>
class ComponentMapper
{
public:
	ComponentMapper();
	~ComponentMapper();

	T& get(int componentId);

	template<class... Args>
	T& emplace(int componentId, Args && ...args);

	template<class... Args>
	T& put(int componentId, T& component);


	static const int componentId;

private:
	HashedArrayTree<chunkSize, T> components;
};

template<class T, int chunkSize>
const int ComponentMapper<T, chunkSize>::componentId = __next_component_id++;

template<class T, int chunkSize>
inline ComponentMapper<T, chunkSize>::ComponentMapper()
{
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
template<class ...Args>
inline T & ComponentMapper<T, chunkSize>::emplace(int componentId, Args && ...args)
{
	components.put(componentId, std::forward<Args>args...);
	return components.at(componentId);
}

template<class T, int chunkSize>
template<class ...Args>
inline T & ComponentMapper<T, chunkSize>::put(int componentId, T & component)
{
	components.put(componentId, component);
	return component;
}
