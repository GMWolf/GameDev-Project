#pragma once
#include "System.h"
#include "Entity.h"

class SystemProfiler : public ECS::System
{
public:
	SystemProfiler();
	~SystemProfiler();

	void init() override;
	void update() override;
	void end() override;

private:
	std::vector<std::deque<std::pair<float, float>>> systemPlots;
	std::vector<float> fpsPlot;

	void logSystem(unsigned int systemId, float pureValue, float totalValue);
	float getSystemSmoothed(int systemId);
};

