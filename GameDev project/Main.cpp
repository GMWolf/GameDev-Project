#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <VertexFormat.h>
#include <Vector3.h>
#include <Vector2.h>
#include <Vector4.h>
#include <string>
#include <iostream>
#include <Shader.h>
#include <ShaderProgram.h>
#include <VertexBuffer.h>
#include <Model.h>
#include <Material.h>
#include <Texture.h>
#include <Pool.h>
#include <VBBuilder.h>
#include <Renderer.h>

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";

	//Game game;
	Renderer game(config.width, config.height);
	glfwApplication app(game, config);
	app.init();

	return 0;
}