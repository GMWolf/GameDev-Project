#pragma once

namespace ECS {

	class System
	{
	public:
		System();
		virtual ~System();

		virtual void init() = 0;
		virtual void update() = 0;
		virtual void end() = 0;

		float getTotalTimeTaken()
		{
			return lastTotalTime;
		}
		float getPureTimeTaken()
		{
			return lastPureTime;
		}
		friend class SystemManager;


		bool enabled = true;
	private:
		float lastPureTime = 0;
		float lastTotalTime = 0;
	};

}