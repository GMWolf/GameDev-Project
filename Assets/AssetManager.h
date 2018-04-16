#pragma once
#include <map>
#include "AssetHandle.h"
#include "AssetLoader.h"
#include "Pool.h"

class BaseAssetManager
{
public:
	virtual ~BaseAssetManager() = default;;
};

template<class T>
class AssetManager : public BaseAssetManager
{
public:
	AssetManager(AssetLoader* loader);
	~AssetManager();

	AssetHandle<T> get(std::string file);
	AssetHandle<T> manage(T* asset, std::string name);
	T& getAsset(AssetHandle<T>& handle);

	void reload(std::string file);

private:
	Pool<T> pool;

	std::map<std::string, AssetHandle<T>> itemMap;

	std::vector<T*> items; //AssetID to pointer
	int nextId;
	AssetLoader* loader;
};

template <class T>
AssetManager<T>::~AssetManager()
{
}

template <class T>
AssetManager<T>::AssetManager(AssetLoader* loader): loader(loader), nextId(0), pool(16)
{
}

template <class T>
AssetHandle<T> AssetManager<T>::get(std::string file)
{
	if (itemMap.find(file) == itemMap.end())
	{	
		//Load into new location
		T* location = pool.get();
		loader->load(file, location);

		//Add to manager
		manage(location, file);
	}

	return itemMap[file];
	
}

template <class T>
AssetHandle<T> AssetManager<T>::manage(T* asset, std::string name)
{
	int assetId = nextId++;

	items.emplace(items.begin() + assetId, asset);
	itemMap.insert({ name, AssetHandle<T>(assetId) });

	return itemMap[name];
}

template <class T>
T& AssetManager<T>::getAsset(AssetHandle<T>& handle)
{
	return *items[handle.assetId];
}

template <class T>
void AssetManager<T>::reload(std::string file)
{
	if (itemMap.find(file) != itemMap.end())
	{
		loader->load(file, items[get(file).assetId]);
	}
}
