#include "Material.h"



Material::Material(ShaderProgram* shader) : shader(shader)
{
}


Material::~Material()
{
}

void Material::apply()
{
	shader->use();

}
