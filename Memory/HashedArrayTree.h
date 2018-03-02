#pragma once
#include <vector>
#include <bitset>
#include <deque>
template<int chunkSize, class T>
class HashedArrayTree {
public:

	T& at(const int i) const;
	void put(const int i, T& o);

	template<class... Args>
	void emplace(const int i, Args&&... args);
	
	void erase(const int i);
	T& operator[](const int i);

private:

	struct Chunk {
		Chunk();

		T& operator[](int i);

		T& at(int i);

		template<class... Args>
		void emplace(const int i, Args&&... args);

		void put(const int i, T& o);

		T* data;
		std::bitset<chunkSize> usage;
	};

	//Trailing return type to solve parser errors.
	auto getChunk() -> Chunk*;
	void ensureChunk(int i);

	std::vector<Chunk*> chunks;
	std::deque<Chunk*> chunkPool;
};

template<int chunkSize, class T>
inline T & HashedArrayTree<chunkSize, T>::at(const int i) const
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	if (chunks[chunkIndex] == nullptr) {
		throw std::out_of_range("i");
	}

	return chunks[chunkIndex]->at(objIndex);
}

template<int chunkSize, class T>
inline void HashedArrayTree<chunkSize, T>::put(const int i, T & o)
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	ensureChunk(chunkIndex);
	chunks[chunkIndex]->put(i, o);
}

template<int chunkSize, class T>
inline void HashedArrayTree<chunkSize, T>::erase(const int i)
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	if (chunks[chunkIndex] == nullptr) {
		throw std::out_of_range("i");
	}

	chunks[chunkIndex]->usage.reset(objIndex);
	if (chunks[chunkIndex]->usage.none()) {
		chunkPool.push_back(chunks[chunkIndex]);
		chunks[chunkIndex] = nullptr;
	}
}

template<int chunkSize, class T>
inline T & HashedArrayTree<chunkSize, T>::operator[](const int i)
{
	int chunkIndex = i / chunkIndex;
	int objIndex = i % chunkIndex;
	return (*chunks[chunkIndex])[objIndex];
}


template<int chunkSize, class T>
inline auto HashedArrayTree<chunkSize, T>::getChunk() -> Chunk*
{
	if (chunkPool.empty()) {
		return new Chunk();
	}
	else {
		Chunk* chunk = chunkPool.front();
		chunkPool.pop_front();
		return chunk;
	}
}

template<int chunkSize, class T>
inline void HashedArrayTree<chunkSize, T>::ensureChunk(int i)
{
	if (chunks.size() <= i) {
		chunks.resize(i+1, nullptr);
		
	}

	if (chunks[i] == nullptr) {
		chunks[i] = getChunk();
		chunks[i]->usage.reset();
	}
}

template<int chunkSize, class T>
template<class ...Args>
inline void HashedArrayTree<chunkSize, T>::emplace(const int i, Args && ...args)
{
	int chunkIndex = i / chunkSize;
	int objIndex = i % chunkSize;

	ensureChunk(chunkIndex);
	
	chunks[chunkIndex]->emplace(objIndex, std::forward<Args> args...);
}

template<int chunkSize, class T>
template<class ...Args>
inline void HashedArrayTree<chunkSize, T>::Chunk::emplace(const int i, Args && ...args) {
	new (data + i) T(std::forward<Args> args...);
	usage.set(i);
}

template<int chunkSize, class T>
inline HashedArrayTree<chunkSize, T>::Chunk::Chunk() {
	data = (T*)std::malloc(sizeof(T) * chunkSize);
}

template<int chunkSize, class T>
inline T & HashedArrayTree<chunkSize, T>::Chunk::operator[](int i)
{
	return data[i];
}

template<int chunkSize, class T>
inline T & HashedArrayTree<chunkSize, T>::Chunk::at(int i)
{
	if (!usage[i]) {
		throw std::out_of_range("i");
	}

	return data[i];
}

template<int chunkSize, class T>
inline void HashedArrayTree<chunkSize, T>::Chunk::put(const int i, T & o)
{
	data[i] = o;
	usage.set(i);
}
