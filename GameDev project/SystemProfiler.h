#pragma once
#include "System.h"
#include "Entity.h"

class SystemProfiler : public System
{
public:
	SystemProfiler();
	~SystemProfiler();

	void init() override;
	void update() override;
	void end() override;

private:
	std::vector<std::deque<float>> systemPlots;
	std::vector<float> fpsPlot;

	void logSystem(int systemId, float value);
	float getSystemSmoothed(int systemId);
};

