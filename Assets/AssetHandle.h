#pragma once

template<class T>
class AssetHandle
{
public:
	AssetHandle() : assetId(-1), counter(nullptr)
	{
	}

	AssetHandle(const AssetHandle<T>& cpy) : assetId(cpy.assetId), counter(cpy.counter)
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
		if (counter != nullptr) {
			(*counter)++;
		}
		return *this;
	}

	int assetId;

	AssetHandle(int assetId) : assetId(assetId)
	{
		counter = new int(1);
	}

private:
	int* counter;
};