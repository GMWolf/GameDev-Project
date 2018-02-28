#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <ApplicationAdapter.h>
#include <ShaderProgram.h>
#include <Shader.h>
#include <Mesh.h>
#include <Model.h>
#include <Texture.h>
#include <Matrix4.h>
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

	int width;
	int height;

	GLuint fbo;
	GLuint diffuseTexture;
	GLuint normalTexture;
	GLuint depthTexture;

	ShaderProgram* geometryProgram;
	Mesh* mesh;
	Model* model;
	Texture* texture;
	Matrix4 projection;
	Matrix4 view;
};

