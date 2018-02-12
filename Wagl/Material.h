#pragma once
#include "ShaderProgram.h"
#include <string>
#include "Vector3.h"
#include <map>
#include <tuple>
class Material
{
public:
	Material(ShaderProgram* shader);
	~Material();

	void apply();


private:

	ShaderProgram* shader;
};

