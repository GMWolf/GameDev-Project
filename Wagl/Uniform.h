#pragma once

template<class T>
class Uniform {
public:
	friend class Material;

	Uniform(std::string name) : name(name){
		
	}

	void operator=(T rhs) {
		value = rhs;
	}

	
private:
	T value;
	int location;
};