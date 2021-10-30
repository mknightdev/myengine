#include "Core.h"
#include "Environment.h"

namespace myengine
{
	std::shared_ptr<Environment> Environment::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;
		return rtn;
	}

	float Environment::getDeltaTime()
	{
		float diff = currentTime - lastTime;
		return deltaTime = diff / 1000.0f;
	}

	void Environment::tick()
	{
		onTick();
	}

	void Environment::onTick()
	{
		lastTime = SDL_GetTicks();
	}

	void Environment::setCurrentTime(float _currentTime)
	{
		currentTime = _currentTime;
	}
}