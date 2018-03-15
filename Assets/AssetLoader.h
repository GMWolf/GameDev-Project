#pragma once
class Assets;

template<class T>
class AssetLoader
{
public:
	AssetLoader(Assets& assets);
	~AssetLoader();

	void load(std::string file, T& asset);

protected:
	Assets & assets;
};

#include "Assets.h"
template <class T>
AssetLoader<T>::AssetLoader(Assets& assets) : assets(assets)
{
}

template <class T>
AssetLoader<T>::~AssetLoader()
{
}

