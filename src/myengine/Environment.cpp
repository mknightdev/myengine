#include "Core.h"
#include "Environment.h"

namespace myengine
{
	std::shared_ptr<Environment> Environment::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();	// This becomes the instance
		rtn->core = _core;
		return rtn;
	}

	float Environment::getDeltaTime()
	{
		return deltaTime;
	}

	void Environment::tick()
	{
		onTick();
	}

	void Environment::onTick()
	{

	}
}