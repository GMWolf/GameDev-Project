#pragma once

template<class T>
class AssetManager;

template<class T>
class AssetHandle
{
public:
	AssetHandle() : assetId(-1), counter(nullptr)
	{
	}

	AssetHandle(const AssetHandle<T>& cpy) : assetId(cpy.assetId), counter(cpy.counter)
	{
		(*counter)++;
	}

	~AssetHandle()
	{
		(*counter)--;
	}

	AssetHandle& operator=(const AssetHandle<T> const & rhs)
	{
		(*counter)--;
		assetId = rhs.assetId;
		counter = rhs.counter;
		(*counter)++;
		return *this;
	}

	T& operator()();

	int assetId;
private:
	AssetHandle(AssetManager<T>& manager, int assetId) : manager(manager), assetId(assetId)
	{
		counter = new int(1);
	}
	int* counter;

	AssetManager<T>& manager;
};

#include "AssetManager.h"
template <class T>
T& AssetHandle<T>::operator()()
{
	return manager.getAsset(*this);
}
