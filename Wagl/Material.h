#pragma once
#include "ShaderProgram.h"
#include <string>
#include "Uniform.h"
#include "Vector3.h"
#include <map>
#include <tuple>
class Material
{
public:
	Material(ShaderProgram* shader);
	~Material();

	void apply();

	template<class T>
	void set(std::string name, T value) {
		(*reinterpret_cast<Uniform<T>*>(uniforms[name])) = value;
	}

	template<class T>
	T& get(std::string name) {
		return (*reinterpret_cast<Uniform<T>*>(uniforms[name])).value;
	}

private:
	
	std::map<std::string, void*> uniforms;

	ShaderProgram* shader;
};

