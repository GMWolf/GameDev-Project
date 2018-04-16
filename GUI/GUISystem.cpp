#include "GUISystem.h"
#include "SubscriptionManager.h"
#include "Transform.h"
#include "ShaderProgramLoader.h"
#include "TextComponent.h"
#include "DeltaTime.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw_gl3.h"
#include "SystemManager.h"
#include <filesystem>


GUISystem::GUISystem(int width, int height, GLFWwindow* window) :
	textEntities(ECS::SubscriptionManager::getSubscription(ECS::Aspect::getAspect<TextComponent, Transform>())),
	window(window)
{
}


GUISystem::~GUISystem()
{
}

void GUISystem::init()
{
	
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	io->DeltaTime = wagl::DeltaTime::delta;
	ImGui_ImplGlfwGL3_NewFrame();
}

void GUISystem::update()
{
	
	
	//textShader->use();
	
	for(ECS::Entity e : textEntities)
	{
		TextComponent& text = e.get<TextComponent>();
		ImGui::Text(text.string.c_str());
	}
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	//Start new frame
	io->DeltaTime = wagl::DeltaTime::delta;
	ImGui_ImplGlfwGL3_NewFrame();
}

void GUISystem::end()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}


