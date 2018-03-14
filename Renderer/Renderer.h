#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Matrix4.h>
#include <FrameBuffer.h>
#include <System.h>
#include <EntitySubscription.h>
#include "LightMesh.h"

class Renderer : public System
{
public:
	Renderer(int width, int height);
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
	wagl::ShaderProgram* lightProgram{};
	wagl::ShaderProgram* resolveProgram{};

	EntitySubscription& renderEntities;
	EntitySubscription& lights;
	EntitySubscription& camera;

	mutable LightMesh lightMesh;

	wagl::ShaderProgram::Uniform u_geometry_MVP;
	wagl::ShaderProgram::Uniform u_geometry_model;
	wagl::ShaderProgram::Uniform u_geometry_normal;
	wagl::ShaderProgram::Uniform u_geometry_roughness;
	wagl::ShaderProgram::Uniform u_geometry_flipNormals;

	wagl::ShaderProgram::Uniform u_light_MVP;
	wagl::ShaderProgram::Uniform u_light_invView;
	wagl::ShaderProgram::Uniform u_light_invProjection;
	wagl::ShaderProgram::Uniform u_light_depth_texture;
	wagl::ShaderProgram::Uniform u_light_nr_texture;

	wagl::ShaderProgram::Uniform u_resolve_light_texture;
	wagl::ShaderProgram::Uniform u_resolve_diffuse_texture;
	wagl::ShaderProgram::Uniform u_resolve_MVP;


	Matrix4 projection;
	Matrix4 view;
};

