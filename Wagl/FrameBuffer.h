#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Texture.h"
#include <vector>
class FrameBuffer
{
public:
	FrameBuffer(int width, int height);
	~FrameBuffer();

	Texture* createTexture(GLenum internalFormat, GLenum format, GLenum type, GLenum attachement, bool drawBuffer);
	
	void bindRead();
	void bindDraw();
	void bind();

	void blit(GLenum attachement, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
	
	GLenum status();

private:
	GLuint fbo;

	std::vector<Texture*> textures;
	std::vector<GLenum> drawBuffers;

	unsigned int width;
	unsigned int height;
};

