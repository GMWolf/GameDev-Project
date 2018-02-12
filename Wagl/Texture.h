#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <SOIL.h>
class Texture
{
public:
	Texture(std::string file, bool mipmap = true, bool compress = false);
	~Texture();

private:

	GLuint glTex;
};

