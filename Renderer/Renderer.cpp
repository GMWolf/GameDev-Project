#include "stdafx.h"
#include "Renderer.h"
#include <iostream>
#include <Transform.h>
#include "MeshFilter.h"
#include "Lights.h"
#include "Camera.h"
#include "ShaderProgramLoader.h"
#include "Assets.h"
#include <ECS.h>


Renderer::Renderer(int width, int height, Assets& assets)
	: width(width), height(height),
	  renderEntities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, MeshFilter>())),
	  pointLights(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Transform, PointLight>())),
	  dirLights(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<DirectionalLight>())),
	  camera(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<Camera>())),
	  quad_vb({{GL_FLOAT, 3, "position"}}, GL_STATIC_DRAW),
	  quad_va(quad_vb),
	  assets(assets), 
	  textureLoader(nullptr), materialLoader(nullptr), rmLoader(nullptr)
{
}


Renderer::~Renderer()
{
}

void Renderer::init()
{
	textureLoader = new TextureLoader;
	assets.registerLoader<wagl::Texture>(textureLoader);
	materialLoader = new MaterialLoader(assets);
	assets.registerLoader<Material>(materialLoader);
	rmLoader = new RenderMeshLoader(assets);
	assets.registerLoader<RenderMesh>(rmLoader);


	ECS::registerLoader<MeshFilter>(new MeshFilterLoader(assets));

	/*shaderLoader = new ShaderProgramLoader;
	assets.registerLoader<ShaderProgramLoader>(shaderLoader);*/

	//glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	GenerateFBO();
	generateQuad();

	geometryProgram = ShaderProgramLoader::load("shaders/geometry.shd");
	
	resolveProgram = ShaderProgramLoader::load("shaders/resolve.shd");
	resolveProgram->Getuniform("screenSize") = glm::vec2(width, height);
	
	pointLightProgram = ShaderProgramLoader::load("shaders/pointLight.shd");
	pointLightProgram->Getuniform("screenSize") = glm::vec2(width, height);

	dirLightProgram = ShaderProgramLoader::load("shaders/dirLight.shd");
	dirLightProgram->Getuniform("screenSize") = glm::vec2(width, height);

	
	u_geometry_MVP = geometryProgram->Getuniform("MVP");
	u_geometry_model = geometryProgram->Getuniform("model");
	u_geometry_normal = geometryProgram->Getuniform("normalTex");
	u_geometry_roughness = geometryProgram->Getuniform("roughnessTex");
	u_geometry_alpha = geometryProgram->Getuniform("alphaTex");
	u_geometry_use_alpha = geometryProgram->Getuniform("useAlpha");
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
	u_resolve_alpha_texture = resolveProgram->Getuniform("alphaTex");
	u_resolve_use_alpha = resolveProgram->Getuniform("useAlpha");
	u_resolve_MVP = resolveProgram->Getuniform("MVP");

	
	projection = glm::perspective<float>(glm::radians(60.f), width / (float)height, 0.1f, 1000.f); 
	view = glm::lookAt(glm::vec3(0, 5, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void Renderer::update()
{
	ECS::Entity camEntity = camera.getFirst();
	view = camEntity.get<Camera>().view;

	render();
}

void Renderer::render() const
{
	glClearColor(0, 0, 0, 0);

	geometryPass();
	lightPass();
	resolvePass();
	
	//geometryBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, 0, 0, width / 4, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	//lightBuffer->blit(GL_COLOR_ATTACHMENT0, 0, 0, width, height, width / 4, 0, width /2, height / 4, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void Renderer::end()
{
	delete textureLoader;
	delete materialLoader;
	delete rmLoader;
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
	u_geometry_alpha = 2;

	u_geometry_flipNormals = true;

	const glm::mat4 mv = projection * view;
	for (ECS::Entity e : renderEntities) {
		const glm::mat4 model = e.get<Transform>().getMatrix();
		u_geometry_MVP = mv * model ;
		u_geometry_model = model;
		Material& material = assets.resolve(e.get<MeshFilter>().material);
		assets.resolve(material.normal).bind(0);
		assets.resolve(material.roughness).bind(1);
		if (material.useAlpha) {
			assets.resolve(material.alpha).bind(2);
			u_geometry_use_alpha = true;
		}
		else
		{
			u_geometry_use_alpha = false;
		}
		
		//std::cout << e.getId() << std::endl;
		assets.resolve(e.get<MeshFilter>().mesh).submit();
	}
	/*for(const RenderObject& o : renderPlan.renderObjects)
	{
		u_geometry_MVP = mv * o.modelMatrix;
		u_geometry_model = o.modelMatrix;
		Material& material = o.material();
		material.normal().bind(0);
		material.roughness().bind(1);
		o.mesh().submit();
	}*/
}

void Renderer::lightPass() const
{

	pointLightMesh.clear();

	for(ECS::Entity light : pointLights)
	{
		Transform& t = light.get<Transform>();
		PointLight& pl = light.get<PointLight>();

		pointLightMesh.addLight(t.getPosition(), pl.colour * pl.power, pl.radius);
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
	u_point_light_invView = glm::inverse(view);
	u_point_light_invProjection = glm::inverse(projection);

	depthTexture->bind(0);
	u_point_light_depth_texture = 0;

	NRTexture->bind(1);
	u_point_light_nr_texture = 1;
	pointLightProgram->use();
	pointLightMesh.submit();

	//Dir light

	u_dir_light_invView = glm::inverse(view);
	u_dir_light_invProjection = glm::inverse(projection);
	u_dir_light_depth_texture = 0;
	u_dir_light_nr_texture = 1;
	dirLightProgram->use();

	quad_va.bind();
	for(ECS::Entity e : dirLights)
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
	u_resolve_alpha_texture = 2;

	resolveProgram->use();
	const glm::mat4 mv = projection * view;
	for (ECS::Entity e : renderEntities) {
		const glm::mat4 model = e.get<Transform>().getMatrix();
		u_resolve_MVP = mv * model;
		//std::cout << e.getId() << '\n';
		Material& material = assets.resolve(e.get<MeshFilter>().material);
		assets.resolve(material.diffuse).bind(1);
		if (material.useAlpha) {
			assets.resolve(material.alpha).bind(2);
			u_resolve_use_alpha = true;
		} else
		{
			u_resolve_use_alpha = false;
		}
		assets.resolve(e.get<MeshFilter>().mesh).submit();
	}
	/*for(const RenderObject& o : renderPlan.renderObjects)
	{
		u_resolve_MVP = mv * o.modelMatrix;
		o.material().diffuse().bind(1);
		o.mesh().draw();
	}*/
}

void Renderer::generateQuad()
{
	glm::vec3 pos[] = {
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
