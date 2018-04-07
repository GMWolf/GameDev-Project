#pragma once
#include <map>
#include "AssetHandle.h"
#include "HashedArrayTree.h"
#include "AssetLoader.h"
#include <vector>
#include <iostream>

template<class T>
class AssetManager
{
public:
	AssetManager(AssetLoader<T>& loader);
	~AssetManager();

	AssetHandle<T> get(std::string file);
	AssetHandle<T> manage(T& asset, std::string name);
	T& getAsset(AssetHandle<T>& handle);

	void reload(std::string file);

private:
	std::map<std::string, AssetHandle<T>> itemMap;
	HashedArrayTree<16, T> items;
	int nextId;
	AssetLoader<T>& loader;
};

template <class T>
AssetManager<T>::AssetManager(AssetLoader<T>& loader): loader(loader), nextId(0)
{
}

template <class T>
AssetManager<T>::~AssetManager()
{
}

template <class T>
AssetHandle<T> AssetManager<T>::get(std::string file)
{
	if (itemMap.find(file) == itemMap.end())
	{
		int assetId = nextId++;

		items.emplace(assetId);
		loader.load(file, items[assetId]);

		//itemMap[file] = AssetHandle<T>(this, assetId);
		itemMap.insert({ file, AssetHandle<T>(this, assetId) });
	}

	return itemMap[file];
	
}

template <class T>
AssetHandle<T> AssetManager<T>::manage(T& asset, std::string name)
{
	int assetId = nextId++;

	items.emplace(assetId, asset);
	itemMap.insert({ name, AssetHandle<T>(this, assetId) });

	return itemMap[name];
}

template <class T>
T& AssetManager<T>::getAsset(AssetHandle<T>& handle)
{
	return items[handle.assetId];
}

template <class T>
void AssetManager<T>::reload(std::string file)
{
	if (itemMap.find(file) != itemMap.end())
	{
		loader.load(file, get(file));
	}
}

