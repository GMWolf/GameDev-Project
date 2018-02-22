#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glfwApplication.h>
#include <ApplicationAdapter.h>
#include <VertexFormat.h>
#include <VertexBuffer.h>
#include <Vector3.h>
#include <Vector2.h>
#include <Vector4.h>
#include <string>
#include <iostream>
#include <Shader.h>
#include <ShaderProgram.h>
#include <Mesh.h>
#include <Model.h>
#include <Material.h>
#include <Texture.h>
#include <Pool.h>
#include <MeshBuilder.h>
#include <Renderer.h>
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

		MeshBuilder builder(format);
		builder.set(VertexAttribute::POSITION, {
			Vector3(-0.5f, 0.5f, 0.0f),
			Vector3(0.5f,  0.5f, 0.0f),
			Vector3(0.5f, -0.5f, 0.0f),
			Vector3(-0.5f, -0.5f, 0.0f)
		});
		builder.set(VertexAttribute::TEXTURE_COORDINATES, {
			Vector2(0.0f, 1.0f),
			Vector2(1.0f, 1.0f),
			Vector2(1.0f, 0.0f),
			Vector2(0.0f, 0.0f)
		});
		builder.set(VertexAttribute::COLOUR, {
			Vector4(1.0f, 0.0f, 0.0f, 1.0f),
			Vector4(0.0f, 1.0f, 0.0f, 1.0f),
			Vector4(0.0f, 0.0f, 1.0f, 1.0f),
			Vector4(1.0f, 1.0f, 1.0f,1.0f)
		});
		builder.setElems({
			0,1,2,2,3,0
		});

		mesh = builder.build();

		texture = new Texture("textures/texture.jpg");
		appleTex = new Texture("textures/apple.jpg");

		texture->bind(0);
		basicProgram->Getuniform("tex") = 0;

		appleTex->bind(1);
		basicProgram->Getuniform("tex2") = 1;

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
	Texture* appleTex;
	Model* model;
};

int main(void) {

	glfwConfiguration config;
	config.title = "yo!";

	//Game game;
	Renderer game(config.width, config.height);
	glfwApplication app(game, config);
	app.init();

	return 0;
}