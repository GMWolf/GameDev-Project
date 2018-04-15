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
	io->DeltaTime = wagl::DeltaTime::delta;
	ImGui_ImplGlfwGL3_NewFrame();
	//textShader->use();
	
	for(Entity e : textEntities)
	{
		TextComponent& text = e.get<TextComponent>();
		ImGui::Text(text.string.c_str());
	}

	fpsPlot.emplace_back(1.0f / static_cast<float>(wagl::DeltaTime::delta));
	if (fpsPlot.size() > 240)
	{
		fpsPlot.erase(fpsPlot.begin());
	}

	ImGui::Begin("Profile");

	float avFPS = 0;
	for(float f : fpsPlot)
	{
		avFPS += f;
	}
	avFPS /= static_cast<float>(fpsPlot.size());

	ImGui::Text("FPS: %f", avFPS);
	ImGui::PlotLines("fps: ", fpsPlot.data(), fpsPlot.size(), 0, 0);

	ImGui::BeginChild("scrolling");
	for(unsigned int i = 0; i < SystemManager::systems.size(); ++i)
	{
		System& system = *SystemManager::systems[i];
		logSystem(i, system.getTimeTaken());

		ImGui::Text("%s: %f", typeid(system).name(),getSystemSmoothed(i));
		
		ImGui::PlotLines("", systemPlots[i].data(), systemPlots[i].size());
	}
	ImGui::EndChild();
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

void GUISystem::logSystem(int systemId, float value)
{
	if (systemId >= systemPlots.size())
	{
		systemPlots.resize(systemId + 1);
	}
	systemPlots[systemId].push_back(value);

	if (systemPlots[systemId].size() > 240)
	{
		systemPlots[systemId].erase(systemPlots[systemId].begin());
	}
}

float GUISystem::getSystemSmoothed(int systemId)
{
	float total = 0;
	for(float f : systemPlots[systemId])
	{
		total += f;
	}

	return total / systemPlots[systemId].size();
}
