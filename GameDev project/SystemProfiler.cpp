#include "SystemProfiler.h"
#include "Transform.h"
#include "TextComponent.h"
#include <DeltaTime.h>
#include "imgui.h"
#include "SystemManager.h"


SystemProfiler::SystemProfiler()
{
}


SystemProfiler::~SystemProfiler()
{
}

void SystemProfiler::init()
{
}

void SystemProfiler::update()
{
	fpsPlot.emplace_back(1.0f / static_cast<float>(wagl::DeltaTime::delta));
	if (fpsPlot.size() > 120)
	{
		fpsPlot.erase(fpsPlot.begin());
	}

	ImGui::Begin("Profile");

	float avFPS = 0;
	for (float f : fpsPlot)
	{
		avFPS += f;
	}
	avFPS /= static_cast<float>(fpsPlot.size());
	float frame = static_cast<float>(wagl::DeltaTime::delta);
	ImGui::Text("frame time: % f. FPS: %f", frame, avFPS);
	ImGui::PlotLines("", fpsPlot.data(), fpsPlot.size(), 0, 0);
	ImGui::BeginGroup();
	ImGui::BeginChild("scrolling");
	for (unsigned int i = 0; i < SystemManager::systems.size(); ++i)
	{
		System& system = *SystemManager::systems[i];
		logSystem(i, system.getTimeTaken());
		ImGui::Checkbox(typeid(system).name(), &(system.enabled));
		ImGui::Text("Update Time: %f us", getSystemSmoothed(i));
		ImGui::PlotHistogram("", [](void*data, int idx) { return (*static_cast<std::deque<float>*>(data)).at(idx); }, &systemPlots[i], systemPlots[i].size());
	}
	ImGui::EndChild();
	ImGui::EndGroup();
	ImGui::End();


}

void SystemProfiler::end()
{
}

void SystemProfiler::logSystem(int systemId, float value)
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

float SystemProfiler::getSystemSmoothed(int systemId)
{
	float total = 0;
	for (auto f = systemPlots[systemId].begin(); f != systemPlots[systemId].end(); f++)
	{
		total += *f;
	}

	return total / systemPlots[systemId].size();
}
