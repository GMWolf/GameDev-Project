#include "stdafx.h"
#include "Renderer.h"
#include <iostream>
#include <Vector3.h>
#include <Transform.h>
#include "MeshFilter.h"
#include "Lights.h"
#include "Camera.h"
#include "ShaderProgramLoader.h"


Renderer::Renderer(int width, int height)
	: width(width), height(height),
	  renderEntities(SubscriptionManager::getSubscription(Aspect::getAspect<Transform, MeshFilter>())),
	  lights(SubscriptionManager::getSubscription(Aspect::getAspect<Transform, PointLight>())), 
	  camera(SubscriptionManager::getSubscription(Aspect::getAspect<Camera>()))
{
}


Renderer::~Renderer()
{
}

void Renderer::init()
{
	//glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	GenerateFBO();

	geometryProgram = ShaderProgramLoader::Load("shaders/geometry.shd");
	
	resolveProgram = ShaderProgramLoader::Load("shaders/resolve.shd");
	resolveProgram->Getuniform("screenSize") = Vector2(width, height);
	
	lightProgram = ShaderProgramLoader::Load("shaders/light.shd");
	lightProgram->Getuniform("screenSize") = Vector2(width, height);

	std::cout << "geometry\n";
	u_geometry_MVP = geometryProgram->Getuniform("MVP");
	u_geometry_model = geometryProgram->Getuniform("model");
	u_geometry_normal = geometryProgram->Getuniform("normalTex");
	u_geometry_roughness = geometryProgram->Getuniform("roughnessTex");
	std::cout << "light\n";
	u_light_MVP = lightProgram->Getuniform("MVP");
	u_light_invView = lightProgram->Getuniform("invView");
	u_light_invProjection = lightProgram->Getuniform("invProjection");
	u_light_depth_texture = lightProgram->Getuniform("depthTex");
	u_light_nr_texture = lightProgram->Getuniform("NRTex");
	std::cout << "resolve\n";
	u_resolve_light_texture = resolveProgram->Getuniform("lightTex");
	u_resolve_diffuse_texture = resolveProgram->Getuniform("diffuseTex");
	u_resolve_MVP = resolveProgram->Getuniform("MVP");
	u_resolve_model = resolveProgram->Getuniform("model");


	projection = Matrix4::Perspective(0.01, 1000, width / ((float) height), 60);
	view = Matrix4::ViewMatrix(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Renderer::update()
{
	Entity camEntity = camera.getFirst();
	view = camEntity.get<Camera>().view;

	render();
}

void Renderer::render() const
{
	glClearColor(0, 0, 0, 0);

	geometryPass();
	lightPass();
	resolvePass();
	
	geometryBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, 0, 0, width / 4, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	lightBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, width / 4, 0, width /2, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Renderer::end()
{
}

void Renderer::GenerateFBO()
{
	geometryBuffer = new wagl::FrameBuffer(width, height);
	NRTexture = geometryBuffer->createTexture(GL_RGB16F, GL_RGBA, GL_HALF_FLOAT, GL_COLOR_ATTACHMENT0, true);
	depthTexture = geometryBuffer->createTexture(GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_HALF_FLOAT, GL_DEPTH_ATTACHMENT, false);
	
	GLenum status = geometryBuffer->status();
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "geometry FB error, status:" << status << std::endl;
		return;
	}
	std::cout << "geometry FB all good" << std::endl;

	lightBuffer = new wagl::FrameBuffer(width, height);
	lightTexture = lightBuffer->createTexture(GL_RGBA32F, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0, true);

	status = lightBuffer->status();
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "light FB error, status:" << status << std::endl;
		return;
	}
	std::cout << "light FB all good" << std::endl;


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::geometryPass() const
{
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//Geometry pass
	geometryBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	geometryProgram->use();

	u_geometry_normal = 0;
	u_geometry_roughness = 1;

	const Matrix4 mv = projection * view;
	for (Entity e : renderEntities) {
		const Matrix4 model = e.get<Transform>().getMatrix();
		u_geometry_MVP = mv * model ;
		u_geometry_model = model;
		e.get<MeshFilter>().normal->bind(0);
		e.get<MeshFilter>().roughness->bind(1);
		//std::cout << e.getId() << std::endl;
		e.get<MeshFilter>().mesh->draw();
	}
}

void Renderer::lightPass() const
{

	lightMesh.clear();

	for(Entity light : lights)
	{
		Transform& t = light.get<Transform>();
		PointLight& pl = light.get<PointLight>();

		lightMesh.addLight(t.position, pl.colour, pl.radius);
	}

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	//Light pass
	lightBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT);

	//lightProgram->Getuniform("view") = view;
	u_light_MVP = projection * view;
	u_light_invView = view.inverse();
	u_light_invProjection = projection.inverse();

	depthTexture->bind(0);
	u_light_depth_texture = 0;

	NRTexture->bind(2);
	u_light_nr_texture = 2;
	
	lightProgram->use();

	lightMesh.draw();
}

void Renderer::resolvePass() const
{
	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	//Final pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lightTexture->bind(0);
	u_resolve_light_texture = 0;

	//texture->bind(1);
	u_resolve_diffuse_texture = 1;

	resolveProgram->use();
	const Matrix4 mv = projection * view;
	for (Entity e : renderEntities) {
		const Matrix4 model = e.get<Transform>().getMatrix();
		u_resolve_MVP = mv * model;
		u_resolve_model = model;
		//std::cout << e.getId() << '\n';
		e.get<MeshFilter>().texture->bind(1);
		e.get<MeshFilter>().mesh->draw();
	}
}
