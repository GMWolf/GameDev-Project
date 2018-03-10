#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace wagl {

	class Texture
	{
	public:
		Texture(int width, int height, GLenum formatInternal, GLenum format, GLenum type);
		Texture(GLint glTex);
		~Texture();

		void bind();
		void bind(GLint textureUnit);

		bool isBound();

		GLuint glTex;

		static Texture* bound;
	};

}