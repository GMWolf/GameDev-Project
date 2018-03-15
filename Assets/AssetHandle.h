#pragma once

template<class T>
class AssetManager;

template<class T>
class AssetHandle
{

	friend AssetManager<T>;
public:
	AssetHandle() : assetId(-1), counter(nullptr)
	{
	}

	AssetHandle(const AssetHandle<T>& cpy) : assetId(cpy.assetId), counter(cpy.counter), manager(cpy.manager)
	{
		if (counter != nullptr) {
			(*counter)++;
		}
	}

	~AssetHandle()
	{
		if (counter != nullptr) {
			(*counter)--;
			if ((*counter) == 0) {
				delete counter;
			}
		}
	}

	AssetHandle& operator=(const AssetHandle<T> const & rhs)
	{
		if (counter != nullptr) {
			(*counter)--;
		} 
		assetId = rhs.assetId;
		counter = rhs.counter;
		manager = rhs.manager;
		if (counter != nullptr) {
			(*counter)++;
		}
		return *this;
	}

	T& operator()();

	int assetId;
private:
	AssetHandle(AssetManager<T>* manager, int assetId) : manager(manager), assetId(assetId)
	{
		counter = new int(1);
	}

	int* counter;

	AssetManager<T>* manager;
};

#include "AssetManager.h"
template <class T>
T& AssetHandle<T>::operator()()
{
	return manager->getAsset(*this);
}
