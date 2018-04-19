#pragma once
#include <vector>
#include <deque>
#include <assert.h>
#include <algorithm>

template<class T>
class Pool
{
public:

	explicit Pool(unsigned int blockSize);
	~Pool();

	T* get();
	void free(T* t);
	
	void reserve(int n);
private:
	std::deque<T*> chunks;
	std::deque<T*> available;
	int blockSize;
};

template <class T>
Pool<T>::Pool(unsigned int blockSize) : blockSize(blockSize)
{
}

template <class T>
Pool<T>::~Pool()
{
	for(T* chunk : chunks)
	{
		free(chunk);
	}
}

template <class T>
T* Pool<T>::get()
{
	reserve(1); //Ensure we have at least 1 element available
	T* r = available.front();
	available.pop_front();
	return r;
}

template <class T>
void Pool<T>::free(T* t)
{
	available.push_back(t);
}

template <class T>
void Pool<T>::reserve(int n)
{
	int allocSize = n - available.size();
	if (allocSize > 0) {

		allocSize = std::min(n, blockSize); //allocate at least 16 elements;

		T* newChunk = static_cast<T*>(malloc(n * sizeof(T)));
		for(int i = 0; i < allocSize; i++)
		{
			available.push_back(newChunk + i);
		}

		chunks.push_back(newChunk);
	}
}
