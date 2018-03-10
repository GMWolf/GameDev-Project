#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ShaderProgram.h>
#include <Texture.h>
#include <Matrix4.h>
#include "Mesh.h"
#include <FrameBuffer.h>
#include <System.h>
#include <EntitySubscription.h>
#include "LightMesh.h"
#include "Vector2.h"

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

	wagl::Texture* normalTexture{};
	wagl::Texture* depthTexture{};
	wagl::Texture* lightTexture{};

	wagl::ShaderProgram* geometryProgram{};
	wagl::ShaderProgram* lightProgram{};
	wagl::ShaderProgram* resolveProgram{};

	EntitySubscription& renderEntities;
	EntitySubscription& lights;
	EntitySubscription& camera;

	Mesh* quad{};

	mutable LightMesh lightMesh;

	Matrix4 projection;
	Matrix4 view;
};

