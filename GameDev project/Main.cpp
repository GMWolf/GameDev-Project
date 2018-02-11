#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <Vector3.h>
class Game : public ApplicationAdapter {
public:


	virtual void init() override {
		VertexFormat format;
		format.add(VertexAttribute::POSITION);
		format.add(VertexAttribute::COLOUR);
		
		

	}

	virtual void render() override{
		glClearColor(1, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

};

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";

	Game game;
	glfwApplication app(game, config);
	app.init();

	return 0;
}