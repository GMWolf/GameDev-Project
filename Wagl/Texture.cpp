#include "Texture.h"


Texture* Texture::bound;

Texture::Texture(int width, int height, GLenum formatInternal, GLenum format, GLenum type)
{
	Texture* preBound = bound;

	glGenTextures(1, &glTex);
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, formatInternal, width, height, 0, format, type, 0);

	if (preBound) {
		preBound->bind();
	}
}

Texture::Texture(GLint glTex) : glTex(glTex)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &glTex);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, glTex);
	bound = this;
}

void Texture::bind(GLint textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, glTex);
	bound = this;
}

bool Texture::isBound()
{
	return bound == this;
}
