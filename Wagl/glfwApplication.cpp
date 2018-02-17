#include "glfwApplication.h"



glfwApplication::glfwApplication(ApplicationAdapter& app, glfwConfiguration config) 
	: app(app), config(config)
{
}


glfwApplication::~glfwApplication()
{
}

bool glfwApplication::init()
{
	if (!glfwInit()) {
		return false;
	}
	GLFWmonitor* monitor = config.fullScreen ? glfwGetPrimaryMonitor() : NULL;
	GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, NULL);

	if (!window) {
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	app.init();

	while (!glfwWindowShouldClose(window))
	{

		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
		float ratio = frameBufferWidth / (float)frameBufferHeight;
		glViewport(0, 0, frameBufferWidth, frameBufferHeight);
		
		app.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	app.end();

	glfwDestroyWindow(window);

	glfwTerminate();

	return true;
}
