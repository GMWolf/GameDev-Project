#pragma once
#include <unordered_map>
#include <typeindex>
#include "AssetLoader.h"
#include "AssetHandle.h"
#include "AssetManager.h"

class Assets
{
public:
	Assets()
	{
		
	}
	~Assets()
	{
		
	}

	template<class T>
	AssetHandle<T> get(std::string file);

	template<class T>
	T& resolve(AssetHandle<T> ah);
	
	template<class T>
	void registerLoader(AssetLoader* loader);

private:
	std::unordered_map<std::type_index, BaseAssetManager* > managers{};
};

template <class T>
AssetHandle<T> Assets::get(std::string file)
{
	return static_cast<AssetManager<T>*>(managers[typeid(T)])->get(file);
}

template <class T>
T& Assets::resolve(AssetHandle<T> ah)
{
	return static_cast<AssetManager<T>*>(managers[typeid(T)])->getAsset(ah);
}

template <class T>
void Assets::registerLoader(AssetLoader* loader)
{
	managers.insert({ typeid(T) , new AssetManager<T>(loader) });
}

