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


GUISystem::GUISystem(int width, int height, GLFWwindow* window) :
	textEntities(SubscriptionManager::getSubscription(Aspect::getAspect<TextComponent, Transform>())),
	window(window)
{
	projection = glm::ortho(0, width, height, 0);
}


GUISystem::~GUISystem()
{
}

void GUISystem::init()
{
	textShader = ShaderProgramLoader::Load("shaders/text.shd");
	textShader->Getuniform("tex") = 0;
	
	ImGui::CreateContext();
	io = &ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

void GUISystem::update()
{
	io->DeltaTime = 0.1;
	ImGui_ImplGlfwGL3_NewFrame();
	//textShader->use();
	
	for(Entity e : textEntities)
	{
		TextComponent& text = e.get<TextComponent>();
		ImGui::Text(text.string.c_str());
	}

	ImGui::Begin("Profile");
	for(System* system : SystemManager::systems)
	{
		ImGui::Text("%s: %f", typeid(*system).name(),system->getTimeTaken());
	}
	ImGui::End();
	//ImGui::RenderText(ImVec2(0, 0), text.string.c_str());

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUISystem::end()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	delete textShader;
}
