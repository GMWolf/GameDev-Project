#include "stdafx.h"
#include "Renderer.h"
#include <iostream>
#include <Vector4.h>
#include <Vector3.h>
#include <Time.h>
Renderer::Renderer(int width, int height)
	:width(width), height(height)
{

}


Renderer::~Renderer()
{
}

void Renderer::init()
{
	glEnable(GL_DEPTH_TEST);

	GenerateFBO();

	Shader<GL_VERTEX_SHADER> geometryVert("shaders/geometryVert.glsl");
	Shader<GL_FRAGMENT_SHADER> geometryFrag("shaders/geometryFrag.glsl");
	geometryProgram = new ShaderProgram(geometryVert, geometryFrag);

	/*mesh = new Mesh();
	mesh->positions = {
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f,  0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f) 
	};
	mesh->UVs = {
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),
		Vector2(0.0f, 0.0f)
	};
	mesh->normals = {
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f)
	};
	mesh->indices = { 0,1,2,2,3,0 };
	mesh->update();*/
	mesh = new Mesh(Mesh::Cube(Vector3(1, 1, 1)));

	texture = new Texture("textures/texture.jpg");

	texture->bind(0);
	geometryProgram->Getuniform("diffuseTex") = 0;

	projection = Matrix4::Perspective(0.01, 100, width / ((float) height), 60);
	view = Matrix4::ViewMatrix(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	
}

void Renderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	/*if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		std::cout << "yo" << std::endl;
		view.position += view.left * Time::delta;
	}*/
}


void Renderer::render()
{
	bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	if (left) {
		view.position += -(view.left * Time::delta * 2);
	}
	bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	if (right) {
		view.position += (view.left * Time::delta * 2);
	}

	geometryProgram->Getuniform("MVP") = projection * view;

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	frameBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	geometryProgram->use();
	mesh->draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	frameBuffer->bindRead();
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	frameBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	frameBuffer->blit(GL_COLOR_ATTACHMENT1, 0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	/*glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_COLOR_ATTACHMENT1);
	glBlitFramebuffer(0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

	glReadBuffer(GL_DEPTH_ATTACHMENT);
	glBlitFramebuffer(0, 0, width, height, halfWidth, halfHeight, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);*/
}

void Renderer::end()
{
}

void Renderer::GenerateFBO()
{
	frameBuffer = new FrameBuffer(width, height);
	diffuseTexture =  frameBuffer->createTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, true);
	normalTexture = frameBuffer->createTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT1, true);
	depthTexture = frameBuffer->createTexture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT, false);
	
	GLenum status = frameBuffer->status();
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "FB error, status:" << status << std::endl;
		return;
	}
	else {
		std::cout << "FB all good" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
