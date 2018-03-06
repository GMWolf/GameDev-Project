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
class Renderer : public System
{
public:
	Renderer(GLFWwindow* window, int width, int height);
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

	FrameBuffer* geometryBuffer{};
	FrameBuffer* lightBuffer{};

	Texture* positionTexture{};
	Texture* normalTexture{};
	Texture* depthTexture{};
	Texture* lightTexture{};

	ShaderProgram* geometryProgram{};
	ShaderProgram* lightProgram{};
	ShaderProgram* resolveProgram{};

	EntitySubscription& renderEntities;
	EntitySubscription& lights;

	Mesh* quad{};

	GLFWwindow* window;

	Texture* texture{};
	Matrix4 projection;
	Matrix4 view;
};

