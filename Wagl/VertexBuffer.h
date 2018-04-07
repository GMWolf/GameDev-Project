#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VertexFormat.h"
namespace wagl {
	class VertexBuffer
	{
	public:
		friend class Model;
		friend class VertexArray;

		VertexBuffer(VertexFormat format, int usage);
		~VertexBuffer();

		void setVertexData(const int vertexCount, const void* data);
		void setElementsData(const int vertexCount, const void* data);

		void bind();

		int elementCount;
		
	private:
		int usage;
		VertexFormat format;

		union {
			struct {
				GLuint vbo; //vertex buffer object
				GLuint ebo; //element buffer object
			};

			GLuint buffers[2];
		};

	};
}