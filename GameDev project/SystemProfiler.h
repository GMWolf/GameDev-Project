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
	Entity entity;
};

