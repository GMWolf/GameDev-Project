#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stack>

class Texture
{
public:
	Texture(int width, int height, GLenum formatInternal, GLenum format, GLenum type);
	Texture(std::string file, bool mipmap = true, bool compress = false);
	~Texture();

	void bind();
	void bind(GLint textureUnit);

	
	GLuint glTex;

	static std::stack<Texture*> bindStack;
};

