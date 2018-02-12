#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <Vector3.h>
#include <Vector2.h>
#include <string>
#include <iostream>
#include <Shader.h>
#include <ShaderProgram.h>
#include <Mesh.h>
#include <Model.h>
#include <Material.h>
#include <Texture.h>
class Game : public ApplicationAdapter {
public:


	virtual void init() override {
		
		Shader<GL_VERTEX_SHADER> basicVert("shaders/basicVert.glsl");
		Shader<GL_FRAGMENT_SHADER> basicFrag("shaders/basicFrag.glsl");
		basicProgram = new ShaderProgram(basicVert, basicFrag);


		VertexFormat format;
		format.add(VertexAttribute::POSITION);
		format.add(VertexAttribute::TEXTURE_COORDINATES);
		format.add(VertexAttribute::COLOUR);

		mesh = new Mesh(format, GL_STATIC_DRAW);

		float vertices[] = {
			-0.5f, 0.5f, 0.0f,
			0.0f, 1.0f,
			1.0f, 0.0f, 0.0f, 1.0f,

			0.5f,  0.5f, 0.0f, 
			1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,

			0.5f, -0.5f, 0.0f,
			1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 1.0f,

			-0.5f, -0.5f, 0.0f,
			0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,1.0f
		};

		GLuint elements[] = {
			0, 1, 2, 2, 3, 0
		};

		mesh->setVertexData(4, vertices);
		mesh->setElementsData(6, elements);

		texture = new Texture("textures/texture.jpg");

		basicProgram->Getuniform("tex") = texture->glTex;

		model = new Model(mesh, basicProgram);
	}

	virtual void render() override{
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		model->draw();
	}

	virtual void end() override {
		delete model;
		delete mesh;
		delete texture;
		delete basicProgram;
	}

	ShaderProgram* basicProgram;
	Mesh * mesh;
	Texture* texture;
	Model* model;
};

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";

	Game game;
	glfwApplication app(game, config);
	app.init();

	return 0;
}