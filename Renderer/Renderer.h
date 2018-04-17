#pragma once
#include <ShaderProgram.h>
#include <Texture.h>
#include <FrameBuffer.h>
#include <System.h>
#include <EntitySubscription.h>
#include "LightMesh.h"
#include "RenderPlan.h"
#include "EntityEvents.h"
#include "MeshFilter.h"
#include <Assets.h>
#include "TextureLoader.h"
#include "MaterialLoader.h"
#include "RenderMeshLoader.h"
#include "ShaderProgramLoader.h"

class Renderer : public ECS::System
{
public:
	Renderer(int width, int height, Assets& assets);
	~Renderer();

	void update() override;
	void render() const;
	void init() override;
	void end() override;
private:

	void GenerateFBO();

	void geometryPass() const;
	void lightPass() const;
	void resolvePass() const;

	int width;
	int height;

	wagl::FrameBuffer* geometryBuffer{};
	wagl::FrameBuffer* lightBuffer{};

	wagl::Texture* NRTexture{}; //Normal + roughness
	wagl::Texture* depthTexture{};
	wagl::Texture* lightTexture{};

	wagl::ShaderProgram* geometryProgram{};
	wagl::ShaderProgram* pointLightProgram{};
	wagl::ShaderProgram* dirLightProgram{};
	wagl::ShaderProgram* resolveProgram{};


	ECS::EntitySubscription& renderEntities;
	ECS::EntitySubscription& pointLights;
	ECS::EntitySubscription& dirLights;
	ECS::EntitySubscription& camera;

	RenderPlan renderPlan;

	mutable LightMesh pointLightMesh;

	wagl::ShaderProgram::Uniform u_geometry_MVP;
	wagl::ShaderProgram::Uniform u_geometry_model;
	wagl::ShaderProgram::Uniform u_geometry_normal;
	wagl::ShaderProgram::Uniform u_geometry_roughness;
	wagl::ShaderProgram::Uniform u_geometry_alpha;
	wagl::ShaderProgram::Uniform u_geometry_use_alpha;
	wagl::ShaderProgram::Uniform u_geometry_flipNormals;

	wagl::ShaderProgram::Uniform u_point_light_MVP;
	wagl::ShaderProgram::Uniform u_point_light_invView;
	wagl::ShaderProgram::Uniform u_point_light_invProjection;
	wagl::ShaderProgram::Uniform u_point_light_depth_texture;
	wagl::ShaderProgram::Uniform u_point_light_nr_texture;

	wagl::ShaderProgram::Uniform u_dir_light_invView;
	wagl::ShaderProgram::Uniform u_dir_light_invProjection;
	wagl::ShaderProgram::Uniform u_dir_light_depth_texture;
	wagl::ShaderProgram::Uniform u_dir_light_nr_texture;
	wagl::ShaderProgram::Uniform u_dir_light_dir;
	wagl::ShaderProgram::Uniform u_dir_light_colour;

	wagl::ShaderProgram::Uniform u_resolve_light_texture;
	wagl::ShaderProgram::Uniform u_resolve_diffuse_texture;
	wagl::ShaderProgram::Uniform u_resolve_alpha_texture;
	wagl::ShaderProgram::Uniform u_resolve_use_alpha;
	wagl::ShaderProgram::Uniform u_resolve_MVP;

	wagl::VertexBuffer quad_vb;
	wagl::VertexArray quad_va;
	void generateQuad();

	glm::mat4 projection;
	glm::mat4 view;

	Assets& assets;

	TextureLoader* textureLoader;
	MaterialLoader* materialLoader;
	RenderMeshLoader* rmLoader;
	//ShaderProgramLoader* shaderLoader;
};

