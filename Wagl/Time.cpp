#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Time.h"



double Time::delta = 0;

void Time::update()
{
	delta = glfwGetTime();
	glfwSetTime(0);
}
