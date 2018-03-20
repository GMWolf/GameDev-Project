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
	  pointLights(SubscriptionManager::getSubscription(Aspect::getAspect<Transform, PointLight>())),
	  dirLights(SubscriptionManager::getSubscription(Aspect::getAspect<DirectionalLight>())),
	  camera(SubscriptionManager::getSubscription(Aspect::getAspect<Camera>())),
	  quad_vb({ { GL_FLOAT, 3, "position" } }, GL_STATIC_DRAW),
	  quad_va(quad_vb)
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
	generateQuad();

	geometryProgram = ShaderProgramLoader::Load("shaders/geometry.shd");
	
	resolveProgram = ShaderProgramLoader::Load("shaders/resolve.shd");
	resolveProgram->Getuniform("screenSize") = Vector2(width, height);
	
	pointLightProgram = ShaderProgramLoader::Load("shaders/pointLight.shd");
	pointLightProgram->Getuniform("screenSize") = Vector2(width, height);

	dirLightProgram = ShaderProgramLoader::Load("shaders/dirLight.shd");
	dirLightProgram->Getuniform("screenSize") = Vector2(width, height);

	
	u_geometry_MVP = geometryProgram->Getuniform("MVP");
	u_geometry_model = geometryProgram->Getuniform("model");
	u_geometry_normal = geometryProgram->Getuniform("normalTex");
	u_geometry_roughness = geometryProgram->Getuniform("roughnessTex");
	u_geometry_flipNormals = geometryProgram->Getuniform("flipNormals");
	
	u_point_light_MVP = pointLightProgram->Getuniform("MVP");
	u_point_light_invView = pointLightProgram->Getuniform("invView");
	u_point_light_invProjection = pointLightProgram->Getuniform("invProjection");
	u_point_light_depth_texture = pointLightProgram->Getuniform("depthTex");
	u_point_light_nr_texture = pointLightProgram->Getuniform("NRTex");

	u_dir_light_invView = dirLightProgram->Getuniform("invView");
	u_dir_light_invProjection = dirLightProgram->Getuniform("invProjection");
	u_dir_light_depth_texture = dirLightProgram->Getuniform("depthTex");
	u_dir_light_nr_texture = dirLightProgram->Getuniform("NRTex");
	u_dir_light_colour = dirLightProgram->Getuniform("colour");
	u_dir_light_dir = dirLightProgram->Getuniform("lightDir");
	
	u_resolve_light_texture = resolveProgram->Getuniform("lightTex");
	u_resolve_diffuse_texture = resolveProgram->Getuniform("diffuseTex");
	u_resolve_MVP = resolveProgram->Getuniform("MVP");


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

	u_geometry_flipNormals = true;

	const Matrix4 mv = projection * view;
	for (Entity e : renderEntities) {
		const Matrix4 model = e.get<Transform>().getMatrix();
		u_geometry_MVP = mv * model ;
		u_geometry_model = model;
		Material& material = e.get<MeshFilter>().material();
		material.normal().bind(0);
		material.roughness().bind(1);
		//std::cout << e.getId() << std::endl;
		e.get<MeshFilter>().mesh().draw();
	}
}

void Renderer::lightPass() const
{

	pointLightMesh.clear();

	for(Entity light : pointLights)
	{
		Transform& t = light.get<Transform>();
		PointLight& pl = light.get<PointLight>();

		pointLightMesh.addLight(t.position, pl.colour * pl.power, pl.radius);
	}

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	//Light pass
	lightBuffer->bindDraw();
	glClear(GL_COLOR_BUFFER_BIT);

	//pointLightProgram->Getuniform("view") = view;
	u_point_light_MVP = projection * view;
	u_point_light_invView = view.inverse();
	u_point_light_invProjection = projection.inverse();

	depthTexture->bind(0);
	u_point_light_depth_texture = 0;

	NRTexture->bind(1);
	u_point_light_nr_texture = 1;
	pointLightProgram->use();
	pointLightMesh.draw();

	u_dir_light_invView = view.inverse();
	u_dir_light_invProjection = projection.inverse();
	u_dir_light_depth_texture = 0;
	u_dir_light_nr_texture = 1;
	dirLightProgram->use();

	quad_va.bind();
	for(Entity e : dirLights)
	{
		DirectionalLight& light = e.get<DirectionalLight>();

		u_dir_light_dir = light.dir;
		u_dir_light_colour = light.colour * light.power;
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}
	glBindVertexArray(0);
	


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
		//std::cout << e.getId() << '\n';
		e.get<MeshFilter>().material().diffuse().bind(1);
		e.get<MeshFilter>().mesh().draw();
	}
}

void Renderer::generateQuad()
{
	Vector3 pos[] = {
		{-1, -1, 0},
		{1, -1, 0},
		{-1, 1, 0},
		{1, 1, 0}
	};

	int elems[] = {
		0, 1,2, 2, 1, 3
	};

	quad_vb.setVertexData(4, pos);
	quad_vb.setElementsData(6, elems);
}
