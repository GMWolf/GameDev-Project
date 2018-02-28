#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
#include <map>
#include <vector>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include "Texture.h"

class ShaderProgram
{
public:
	struct Uniform {
		Uniform() {
		}

		Uniform(GLuint program, GLint location, GLenum type, GLsizei size)
			:program(program), location(location), type(type), size(size) {
		}

		void operator=(const GLint rhs) const;
		void operator=(const GLuint rhs) const;
		void operator=(const GLfloat rhs) const;
		

		void operator=(const Vector3& rhs) const;
		void operator=(const Vector2& rhs) const;

		void operator=(const Matrix4& rhs) const;

		GLuint program;
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


	const Attribute& GetAttribute(const int index) const;
	const Attribute& GetAttribute(const std::string name) const;
	bool hasAttribute(const std::string attribute) const;
	const Uniform& Getuniform(const std::string uniform) const;

	void use();

private:

	void registerUniforms();
	void registerAttributes();
	void link();

	static bool isSamplerType(GLenum type);

	std::map<std::string, Uniform> uniforms;
	std::vector<Attribute> attributes;
	std::map<std::string, int> attributeIndexMap;

	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint program;
};

