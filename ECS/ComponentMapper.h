#pragma once
#include <HashedArrayTree.h>
#include <utility>

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

	void erase(int componentId);

private:
	HashedArrayTree<chunkSize, T> components;
};


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
inline void ComponentMapper<T, chunkSize>::erase(int componentId)
{
	components.erase(componentId);
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
