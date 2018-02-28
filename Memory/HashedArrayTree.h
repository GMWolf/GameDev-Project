#pragma once
#include <vector>
#include <bitset>
#include <deque>

template<int chunkSize, class T>
class HashedArrayTree {
public:

	T& at(const int i) const;
	put(const int i, T& o);
	erase(const int i);
	T& operator[](const int i);

private:

	T* getChunk();
	ensureChunk(int i);

	std::vector<T*> chunks;
	std::vector<std::bitset<chunkSize>> chunkUsage;
	std::deque<T*> chunkPool;
};

template<int chunkSize, class T>
inline T & HashedArrayTree<T>::at(const int i) const
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	if (chunks[chunkIndex] == nullptr) {
		throw std::out_of_range();
	}

	if (!chunkUsage[chunkIndex][objIndex]) {
		throw std::out_of_range();
	}

	return chunks[chunkIndex][objIndex];
}

template<int chunkSize, class T>
inline HashedArrayTree<T>::put(const int i, T & o)
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	ensureChunk(chunkIndex);
	chunks[chunkIndex][objIndex] = o;
	chunkUsage[chunkIndex].set(objIndex);
}

template<int chunkSize, class T>
inline HashedArrayTree<T>::erase(const int i)
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;
	if (chunks[chunkIndex] == nullptr) {
		throw std::out_of_range();
	}
	chunkUsage[chunkIndex][objIndex] = false;
	if (chunkUsage[chunkIndex].noone()) {
		chunkPool.push_back(chunks[chunkIndex]);
		chunks[chunkIndex] = nullptr;
	}
}

template<int chunkSize, class T>
inline T & HashedArrayTree<T>::operator[](const int i)
{
	int chunkIndex = i / chunkIndex;
	int objIndex = i % chunkIndex;
	return chunks[chunkIndex][objIndex];
}

template<int chunkSize, class T>
inline T * HashedArrayTree<T>::getChunk()
{
	if (chunkPool.empty()) {
		return new T[chunkSize];
	}
	else {
		T* chunk = chunkPool.front();
		chunkPool.pop_front();
		return chunk;
	}
}

template<int chunkSize, class T>
inline HashedArrayTree<T>::ensureChunk(int i)
{
	if (chunks.size() < i) {
		chunks.resize(i, nullptr);
	}

	if (chunks[i] == nullptr) {
		chunks[i] = getChunk();
		chunkUsage[i].resize(chunkSize, false);
	}
}
