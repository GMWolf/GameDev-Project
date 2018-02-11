#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(void) {
	
	if (!glfwInit()) {
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);

	if (!window) {
		return 1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}