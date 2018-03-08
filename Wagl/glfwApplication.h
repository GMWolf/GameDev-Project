#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ApplicationAdapter.h"
#include <string>
struct glfwConfiguration
{
	glfwConfiguration() : glfwConfiguration(640, 480, "Title"){
	}
	glfwConfiguration(int width, int height, std::string)
		: width(width), height(height), title("title"), fullScreen(false) {
	}
	int width;
	int height;
	std::string title;
	bool fullScreen;
};

class glfwApplication
{
public:
	glfwApplication(ApplicationAdapter& app, glfwConfiguration config);
	~glfwApplication();

	bool init();

private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static glfwApplication* appCallback;
	ApplicationAdapter& app;
	glfwConfiguration config;
	int frameBufferWidth;
	int frameBufferHeight;
};

