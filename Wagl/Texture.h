#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
public:
	Texture(std::string file, bool mipmap = true, bool compress = false);
	~Texture();

	void bind();
	void bind(GLint textureUnit);

	GLuint glTex;
};

