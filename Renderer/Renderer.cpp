#include "stdafx.h"
#include "Renderer.h"
#include <iostream>
#include <Vector4.h>
#include <Vector3.h>
#include <DeltaTime.h>
#include <ShaderProgramLoader.h>
#include <ImageLoader.h>

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

	geometryProgram = ShaderProgramLoader::Load("shaders/geometry.shd");
	lightProgram = ShaderProgramLoader::Load("shaders/light.shd");
	resolveProgram = ShaderProgramLoader::Load("shaders/simpleDiffuse.shd");
	resolveProgram->Getuniform("screenSize") = Vector2(width, height);

	lightProgram->Getuniform("screenSize") = Vector2(width, height);
	lightProgram->Getuniform("lightPos") = Vector3(1, 1, 1);
	lightProgram->Getuniform("intensity") = 1.f;
	lightProgram->Getuniform("MVP") = Matrix4::Identity();

	
	MeshData cube = Mesh::Cube(Vector3(1, 1, 1));
	MeshData floor = Mesh::Quad(Vector3(-100, -0.5, -100), Vector3(100, -0.5, -100), Vector3(100, -0.5, 100), Vector3(-100, -0.5, 100),
		Vector2(0,0), Vector2(1, 0), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, 1, 0), Vector3(0, 1, 0), Vector3(0, 1, 0), Vector3(0, 1, 0));

	mesh = new Mesh(cube + floor);

	quad = new Mesh(Mesh::Quad(Vector3(-1, -1, 0), Vector3(1, -1, 0), Vector3(1, 1, 0), Vector3(-1, 1, 0),
		Vector2(0, 0), Vector2(0, 1), Vector2(1, 1), Vector2(0, 1),
		Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0)));

	texture = ImageLoader::Load("textures/texture.jpg");

	/*texture->bind(0);
	geometryProgram->Getuniform("diffuseTex") = 0;*/

	projection = Matrix4::Perspective(0.01, 100, width / ((float) height), 60);
	view = Matrix4::ViewMatrix(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Renderer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void Renderer::render()
{
	bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	if (left) {
		view.position += (view.left * DeltaTime::delta * 2);
	}
	bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	if (right) {
		view.position += -(view.left * DeltaTime::delta * 2);
	}
	bool up = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
	if (up) {
		view.position += -(view.up * DeltaTime::delta * 2);
	}
	bool down = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;
	if (down) {
		view.position += (view.up * DeltaTime::delta * 2);
	}
	bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	if (forward) {
		view.position += (view.forward * DeltaTime::delta * 2);
	}
	bool backward = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
	if (backward) {
		view.position += -(view.forward * DeltaTime::delta * 2);
	}

	glClearColor(1, 1, 1, 1);
	geometryPass();
	lightPass();
	resolvePass();
	
	//geometryBuffer->bindRead();
	geometryBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, 0, 0, width / 4, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	geometryBuffer->blit(GL_COLOR_ATTACHMENT1, 0, 0, width, height, width / 4, 0, width / 2, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	lightBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, width / 2, 0, width * 0.75, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	/*lightBuffer->bindRead();
	lightBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, 0, halfHeight, halfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	*/

}

void Renderer::end()
{
}

void Renderer::GenerateFBO()
{
	geometryBuffer = new FrameBuffer(width, height);
	positionTexture = geometryBuffer->createTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, true);
	normalTexture = geometryBuffer->createTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT1, true);
	depthTexture = geometryBuffer->createTexture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT, false);
	
	GLenum status = geometryBuffer->status();
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "geometry FB error, status:" << status << std::endl;
		return;
	}
	else {
		std::cout << "geometry FB all good" << std::endl;
	}

	lightBuffer = new FrameBuffer(width, height);
	lightTexture = lightBuffer->createTexture(GL_RGB32F, GL_RGB, GL_FLOAT, GL_COLOR_ATTACHMENT0, true);

	status = lightBuffer->status();
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "light FB error, status:" << status << std::endl;
		return;
	}
	else {
		std::cout << "light FB all good" << std::endl;
	}
	

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::geometryPass()
{
	//Geometry pass
	geometryBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	geometryProgram->Getuniform("MVP") = projection * view;
	geometryProgram->use();
	mesh->draw();
}

void Renderer::lightPass()
{
	//Light pass
	lightBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//geometryBuffer->bindRead();
	positionTexture->bind(0);
	lightProgram->Getuniform("positionTex") = 0;

	normalTexture->bind(1);
	lightProgram->Getuniform("normalTex") = 1;

	lightProgram->use();
	quad->draw();
}

void Renderer::resolvePass()
{
	//Final pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lightTexture->bind(0);
	resolveProgram->Getuniform("lightTex") = 0;

	texture->bind(1);
	resolveProgram->Getuniform("diffuseTex") = 1;

	resolveProgram->Getuniform("MVP") = projection * view;
	resolveProgram->use();
	mesh->draw();
}
