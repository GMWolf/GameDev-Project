#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ApplicationAdapter.h>
#include <ShaderProgram.h>
#include <Shader.h>
#include <Texture.h>
#include <Matrix4.h>
#include "Mesh.h"
#include <FrameBuffer.h>
class Renderer : public ApplicationAdapter
{
public:
	Renderer(int width, int height);
	~Renderer();

	virtual void render();
	virtual void init();
	virtual void end();
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:

	void GenerateFBO();

	void geometryPass();
	void lightPass();
	void resolvePass();

	int width;
	int height;

	FrameBuffer* geometryBuffer;
	FrameBuffer* lightBuffer;

	Texture* positionTexture;
	Texture* normalTexture;
	Texture* depthTexture;

	Texture* lightTexture;

	ShaderProgram* geometryProgram;
	ShaderProgram* lightProgram;
	ShaderProgram* resolveProgram;


	Mesh* mesh;
	Mesh* quad;


	Texture* texture;
	Matrix4 projection;
	Matrix4 view;
};

