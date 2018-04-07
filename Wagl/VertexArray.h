#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexBuffer.h"
#include "ShaderProgram.h"

namespace wagl {

	class VertexArray
	{
	public:
		VertexArray(VertexBuffer& vb);
		VertexArray(VertexBuffer& vb, ShaderProgram& shd);
		~VertexArray();

		void bind() const;
		static void unbind();

		void submit(unsigned int elementCount) const;

	private:

		GLuint vao{};
	};

}