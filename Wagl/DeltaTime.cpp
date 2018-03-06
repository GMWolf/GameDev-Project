#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "DeltaTime.h"



double DeltaTime::delta = 0;

void DeltaTime::update()
{
	delta = glfwGetTime();
	glfwSetTime(0);
}
