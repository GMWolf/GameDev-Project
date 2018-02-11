#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <Vector3.h>
#include <string>
#include <iostream>
#include <Shader.h>
#include <ShaderProgram.h>
class Game : public ApplicationAdapter {
public:


	virtual void init() override {
		
		Shader<GL_VERTEX_SHADER> basicVert("shaders/basicVert.glsl");
		Shader<GL_FRAGMENT_SHADER> basicFrag("shaders/basicFrag.glsl");
		ShaderProgram basicProgram(basicVert, basicFrag);
		basicProgram.use();

		VertexFormat format;
		format.add(VertexAttribute::POSITION);
		format.add(VertexAttribute::COLOUR);

		float vertices[] = {
			0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f
		};

		//vb->bufferData(sizeof(vertices), vertices);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		
		GLuint vbo;
		glGenBuffers(1, &vbo);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		for (int i = 0; i < format.attributes.size(); i++) {
			VertexAttribute attribute = format.attributes[i];
			GLint attribPos = basicProgram.GetAttributeLocation(attribute.alias);
			glVertexAttribPointer(attribPos, attribute.elementCount, attribute.type, GL_FALSE, format.getStride(), (void*)format.getOffset(i));
			glEnableVertexAttribArray(attribPos);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	virtual void render() override{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/*glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);*/
	}

	VertexBuffer* vb;
	GLuint vao;
};

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";

	Game game;
	glfwApplication app(game, config);
	app.init();

	return 0;
}