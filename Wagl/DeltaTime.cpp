#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "DeltaTime.h"



double wagl::DeltaTime::delta = 0;

void wagl::DeltaTime::update()
{
	delta = glfwGetTime();
	glfwSetTime(0);
}
