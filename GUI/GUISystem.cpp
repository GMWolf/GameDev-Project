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
	if (fpsPlot.size() > 120)
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
	float frame =static_cast<float>(wagl::DeltaTime::delta);
	ImGui::Text("frame time: % f. FPS: %f", frame, avFPS);
	ImGui::PlotLines("", fpsPlot.data(), fpsPlot.size(), 0, 0);
	ImGui::BeginGroup();
	ImGui::BeginChild("scrolling");
	for(unsigned int i = 0; i < SystemManager::systems.size(); ++i)
	{
		System& system = *SystemManager::systems[i];
		logSystem(i, system.getTimeTaken());
		if (ImGui::Checkbox(typeid(system).name(), &(system.enabled)))
		{
			std::cout << system.enabled << std::endl;
		}
		ImGui::Text("Update Time: %f us", getSystemSmoothed(i));
		ImGui::PlotHistogram("", [](void*data, int idx) { return (*static_cast<std::deque<float>*>(data)).at(idx); }, &systemPlots[i], systemPlots[i].size());
	}
	ImGui::EndChild();
	ImGui::EndGroup();
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
	systemPlots[systemId].emplace_back(value);

	if (systemPlots[systemId].size() > 120)
	{
		systemPlots[systemId].pop_front();
	}
}

float GUISystem::getSystemSmoothed(int systemId)
{
	float total = 0;
	for(auto f = systemPlots[systemId].begin(); f != systemPlots[systemId].end(); f++)
	{
		total += *f;
	}

	return total / systemPlots[systemId].size();
}
