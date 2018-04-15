#pragma once
#include <System.h>
#include "EntitySubscription.h"
#include "ShaderProgram.h"

class ImGuiIO;

class GUISystem : public System
{
public:
	GUISystem(int width, int height, GLFWwindow* window);
	~GUISystem();

	void init() override;
	void update() override;
	void end() override;

private:

	GLFWwindow * window;
	ImGuiIO* io;

	glm::mat4 projection;

	EntitySubscription & textEntities;

	wagl::ShaderProgram* textShader;

	std::vector<std::vector<float>> systemPlots;
	std::vector<float> fpsPlot;

	void logSystem(int systemId, float value);
	float getSystemSmoothed(int systemId);
};

