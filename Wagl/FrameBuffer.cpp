#include "FrameBuffer.h"



FrameBuffer::FrameBuffer(int width, int height) : width(width), height(height)
{
	glGenFramebuffers(1, &fbo);
}


FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &fbo);
	for (Texture* tex : textures) {
		delete tex;
	}
}

Texture * FrameBuffer::createTexture(GLenum internalFormat, GLenum format, GLenum type, GLenum attachement, bool drawBuffer)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	Texture* t = new Texture(width, height, internalFormat, format, type);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachement, GL_TEXTURE_2D, t->glTex, 0);
	if (drawBuffer) {
		drawBuffers.push_back(attachement);
		glDrawBuffers(drawBuffers.size(), drawBuffers.data());
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return t;
}

void FrameBuffer::bindRead()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
}

void FrameBuffer::bindDraw()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::blit(GLenum attachement, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter)
{
	bindRead();
	glReadBuffer(attachement);
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

GLenum FrameBuffer::status()
{
	bind();
	return glCheckFramebufferStatus(GL_FRAMEBUFFER);
}

