#pragma once
#include <System.h>
#include "EntitySubscription.h"
#include "ShaderProgram.h"
#include <queue>

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

	EntitySubscription & textEntities;

	
};

