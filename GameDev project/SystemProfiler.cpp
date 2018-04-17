#include "SystemProfiler.h"
#include "Transform.h"
#include "TextComponent.h"
#include <DeltaTime.h>
#include "imgui.h"
#include "SystemManager.h"
#include "imgui_multigraph.h"


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
	for (unsigned int i = 0; i < ECS::SystemManager::systems.size(); ++i)
	{
		System& system = *ECS::SystemManager::systems[i];
		logSystem(i, system.getPureTimeTaken(), system.getTotalTimeTaken());
		ImGui::Checkbox(typeid(system).name(), &(system.enabled));
		ImGui::Text("Update Time: %f us", getSystemSmoothed(i));

		//ImGui::PlotHistogram("", [](void*data, int idx) { return (*static_cast<std::deque<float>*>(data)).at(idx); }, &systemPlots[i], systemPlots[i].size());
		ImColor colors[] = {
			ImColor(255, 0, 0),
			ImColor(255, 190, 66)
		};
		ImGui::PlotMultiHistogram("", [](void*data, int idg, int idx)
		{
			std::pair<float, float> value = (*static_cast<std::deque<std::pair<float, float>>*>(data)).at(idx);
			return (idg == 0) ? value.second : value.first;
		}, &systemPlots[i], systemPlots[i].size(), 2, colors);
	}
	ImGui::EndChild();
	ImGui::EndGroup();
	ImGui::End();


}

void SystemProfiler::end()
{
}

void SystemProfiler::logSystem(unsigned int systemId, float pureValue, float totalValue)
{
	if (systemId >= systemPlots.size())
	{
		systemPlots.resize(systemId + 1);
	}

	systemPlots[systemId].emplace_back(pureValue, totalValue);

	if (systemPlots[systemId].size() > 120)
	{
		systemPlots[systemId].pop_front();
	}
}

float SystemProfiler::getSystemSmoothed(int systemId)
{
	float total = 0;
	for (auto f = systemPlots[systemId].begin(); f != systemPlots[systemId].end(); ++f)
	{
		total += (*f).second;
	}

	return total / systemPlots[systemId].size();
}
