#pragma once
class System
{
public:
	System();
	virtual ~System();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void end() = 0;
};

