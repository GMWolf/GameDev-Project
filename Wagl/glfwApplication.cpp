#include "glfwApplication.h"
#include "DeltaTime.h"
glfwApplication* glfwApplication::appCallback = nullptr;

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
	glfwSwapInterval(0);
	GLFWmonitor* monitor = config.fullScreen ? glfwGetPrimaryMonitor() : NULL;
	GLFWwindow* window = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor, NULL);

	if (!window) {
		glfwTerminate();
		return false;
	}
	
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	appCallback = this;
	glfwSetKeyCallback(window, keyCallback);

	app.window = window;
	app.init();
	
	while (!glfwWindowShouldClose(window))
	{
		DeltaTime::update();
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

void glfwApplication::keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	appCallback->app.keyCallback(window, key, scancode, action, mods);
}
