#pragma once
#include <vector>
#include <algorithm>
template<class T>
class FlatSet{
public:

	void insert(T&& o);

	void erase(T& o);

	void clear();

	auto begin() const;

	auto end() const;

private:
	std::vector<T> data;
};

template<class T>
inline void FlatSet<T>::insert(T && o)
{
	if (std::find(data.begin(), data.end(), o) == data.end()) {
		data.push_back(std::move(o));
	}
}

template<class T>
inline void FlatSet<T>::erase(T & o)
{
	if (data.size() > 0) {
		iter_swap(std::find(data.begin(), data.end(), o), data.end() - 1);
		data.resize(data.size() - 1);
	}
}

template<class T>
inline void FlatSet<T>::clear()
{
	data.clear();
}

template<class T>
inline auto FlatSet<T>::begin() const
{
	return data.begin();
}

template<class T>
inline auto FlatSet<T>::end() const
{
	return data.end();
}
