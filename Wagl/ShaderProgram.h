#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
#include <map>
class ShaderProgram
{
public:
	struct Uniform {
		Uniform() {
		}

		Uniform(GLint location, GLenum type, GLsizei size)
			: location(location), type(type), size(size) {
		}

		GLenum type;
		GLsizei size;
		GLint location;
	};


	struct Attribute {
		Attribute() {
		}

		Attribute(GLint location, GLenum type, GLsizei size)
			: location(location), type(type), size(size) {
		}
		GLenum type;
		GLsizei size;
		GLint location;
	};

	ShaderProgram(Shader<GL_VERTEX_SHADER>& vertex, Shader<GL_FRAGMENT_SHADER>& fragment);
	~ShaderProgram();


	const Attribute& GetAttribute(const std::string attribute) const;
	bool hasAttribute(const std::string attribute) const;
	const Uniform& Getuniform(const std::string uniform) const;

	void use();

private:

	void registerUniforms();
	void registerAttributes();
	void link();

	std::map<std::string, Uniform> uniforms;
	std::map<std::string, Attribute> attributes;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint program;
};

