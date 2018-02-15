#pragma once
#include <vector>
#include <deque>
#include <assert.h>
template<class T>
class Pool
{
public:

	Pool(const unsigned int blockSize);
	~Pool();

	template<typename... Ts>
	T* create(Ts... args);
	
	void free(T* o);

	void freeUnusedBlocks();

private:

	void addBlock();
	bool isAvailable(T* o);
	bool blockIsFree(T* block);
	void freeBlock(T* block);

	int blockSize;
	std::vector<T*> blocks;
	std::deque<T*> available;
};

template<class T>
inline Pool<T>::Pool(const unsigned int blockSize) : blockSize(blockSize)
{
	assert(blockSize > 0);
}

template<class T>
inline Pool<T>::~Pool()
{
}

template<class T>
inline void Pool<T>::free(T * o)
{
	o->~();
	available.push_back(o);
}

template<class T>
inline void Pool<T>::freeUnusedBlocks()
{
	for (int i = 0; i < blocks.size(); i++) {
		if (blockIsFree(blocks[i])) {
			freeBlock(blocks[i]);
			blocks.erase(blocks.begin() + i);
		}
	}
}

template<class T>
inline void Pool<T>::addBlock() {
	T* newBlock = new T[blockSize];
	blocks.push_back(newBlock);

	for (int i = blockSize - 1; i >= 0; i++) {
		available.push_back(newBlock + i);
	}
}

template<class T>
inline bool Pool<T>::isAvailable(T* o)
{
	return (std::find(available.begin(), available.end(), o) != available.end());
}

template<class T>
inline bool Pool<T>::blockIsFree(T * block)
{
	for (int i = 0; i < blockSize; i++) {
		if (!isAvailable(block + i)) {
			return false;
		}
	}
	return true;
}

template<class T>
inline void Pool<T>::freeBlock(T * block)
{
	assert(blockIsFree(block));
	for (int i = 0; i < blockSize; i++) {
		available.erase(std::find(available.begin(), available.end(), block + i));
	}
	delete[] block;
}

template<class T>
template<typename ...Ts>
inline T * Pool<T>::create(Ts ...args)
{
	if (available.empty()) {
		addBlock();
	}

	T* newT = available.pop_back();
	newT->T(args...);

	return newT;
}
