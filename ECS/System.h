#pragma once
class System
{
public:
	System();
	virtual ~System();

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void end() = 0;

	float getTimeTaken()
	{
		return lastTime;
	}
	friend class SystemManager;
private:
	float lastTime = 0;
};

