#include "stdafx.h"
#include "Renderer.h"
#include <iostream>
#include <MeshBuilder.h>
#include <VertexFormat.h>
#include <Vector4.h>
#include <Vector3.h>

Renderer::Renderer(int width, int height)
	:width(width), height(height)
{

}


Renderer::~Renderer()
{
}

void Renderer::render()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	/*glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model->draw();
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
	int halfWidth = width / 2;
	int halfHeight = height / 2;
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glBlitFramebuffer(0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	
	glReadBuffer(GL_COLOR_ATTACHMENT1);
	glBlitFramebuffer(0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);*/

	model->draw();
	/*
	glReadBuffer(GL_DEPTH_ATTACHMENT);
	glBlitFramebuffer(0, 0, width, height, halfWidth, halfHeight, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	*/
}

void Renderer::init()
{
	GenerateFBO();

	Shader<GL_VERTEX_SHADER> geometryVert("shaders/geometryVert.glsl");
	Shader<GL_FRAGMENT_SHADER> geometryFrag("shaders/geometryFrag.glsl");
	geometryProgram = new ShaderProgram(geometryVert, geometryFrag);


	VertexFormat format;
	format.add(VertexAttribute::POSITION);
	format.add(VertexAttribute::TEXTURE_COORDINATES);
	format.add(VertexAttribute::NORMAL);

	MeshBuilder builder(format);
	builder.set(VertexAttribute::POSITION, {
		/*Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(0.5f,  0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f)*/
		Vector3(-50.0f, 50.0f, 0.0f),
		Vector3(50.0f,  50.0f, 0.0f),
		Vector3(50.0f, -50.0f, 0.0f),
		Vector3(-50.0f, -50.0f, 0.0f)
		});
	builder.set(VertexAttribute::TEXTURE_COORDINATES, {
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f),
		Vector2(0.0f, 0.0f)
		});
	builder.set(VertexAttribute::NORMAL, {
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f),
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f)
		});

	builder.setElems({
		0,1,2,2,3,0
		});

	mesh = builder.build();

	model = new Model(mesh, geometryProgram);

	texture = new Texture("textures/texture.jpg");

	texture->bind(0);
	geometryProgram->Getuniform("diffuseTex") = 0;

	Matrix4 proj = Matrix4::Perspective(0.01, 1000, (float)width / (float)height, 60);
	Matrix4 view = Matrix4::ViewMatrix(Vector3(0, 0, 100), Vector3(0, 0, 0), Vector3(0, 1, 0));
	mvp = view;
	//mvp = Matrix4::Identity();

	geometryProgram->Getuniform("MVP") = mvp;
}

void Renderer::end()
{
}

void Renderer::GenerateFBO()
{
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

	glGenTextures(1, &diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, diffuseTexture, 0);

	glGenTextures(1, &normalTexture);
	glBindTexture(GL_TEXTURE_2D, normalTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTexture, 0);

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "FB error, status:" << status << std::endl;
		return;
	}
	else {
		std::cout << "FB all good" << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
