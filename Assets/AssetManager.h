#pragma once
#include <map>
#include "MaterialLoader.h"
#include "AssetHandle.h"
#include "AssetLoader.h"
#include "HashedArrayTree.h"

class Assets;

template<class T>
class AssetManager
{
public:
	AssetManager(Assets& assets);
	~AssetManager();

	AssetHandle<T> get(std::string file);
	AssetHandle<T> manage(T& asset, std::string name);
	T& getAsset(AssetHandle<T>& handle);

private:
	Assets & assets;
	std::map<std::string, AssetHandle<T>> itemMap;
	AssetLoader<T> loader;
	HashedArrayTree<16, T> items;
	int nextId;
	
};

template <class T>
AssetManager<T>::AssetManager(Assets& assets): assets(assets), nextId(0), loader(assets)
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
		const int assetId = nextId++;
		if (items.size() <= assetId) {
			items.resize(assetId + 1);
		}
		loader.load(file, items[assetId]);
		itemMap[file] = AssetHandle<T>(*this, assetId);
	}

	return itemMap[file];
	
}

template <class T>
AssetHandle<T> AssetManager<T>::manage(T& asset, std::string name)
{
	const int assetId = nextId++;
	if (items.size() <= assetId) {
		items.resize(assetId + 1);
	}
	items[assetId] = asset;
	itemMap[name] = AssetHandle<T>(*this, assetId);
	return itemMap[name];
}

template <class T>
T& AssetManager<T>::getAsset(AssetHandle<T>& handle)
{
	return items[handle.assetId];
}

