#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class ApplicationAdapter {

public:
	virtual ~ApplicationAdapter() = default;
	virtual void render() = 0;
	virtual void init();
	virtual void end();
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	GLFWwindow* window;
	
	bool ShouldClose;
};
