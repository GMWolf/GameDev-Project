#pragma once
#include <string>

template<class T>
class AssetLoader {
public: 
	void load(std::string file, T& location);
};