#include "Core.h"
#include "Environment.h"

namespace myengine
{
	std::shared_ptr<Environment> Environment::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;

		// Initialise to zero
		rtn->deltaTime = 0.0f;
		rtn->lastTime = 0.0f;
		rtn->currentTime = 0.0f;

		return rtn;
	}

	float Environment::getDeltaTime()
	{
		currentTime = SDL_GetTicks();
		float diff = currentTime - lastTime;
		lastTime = currentTime;
		return deltaTime = diff / 1000.0f;
	}

	void Environment::tick()
	{
		onTick();
	}

	void Environment::onTick()
	{

	}
}