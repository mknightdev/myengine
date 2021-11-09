#include "Core.h"
#include "Environment.h"
#include <Windows.h>

namespace myengine
{
	std::shared_ptr<Environment> Environment::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;

		// Initialise to zero
		rtn->deltaTime = 0.0f;
		//rtn->lastTime = 0.0f;
		rtn->currentTime = 0.0f;

		return rtn;
	}

	float Environment::getDeltaTime()
	{
		return deltaTime;
	}

	void Environment::tick()
	{
		currentTime = SDL_GetTicks();
		float diff = currentTime - lastTime;
		deltaTime = diff / 1000.0f;
		lastTime = currentTime;

		//currentTime = GetTickCount();


		//float diff = currentTime - lastTime;
		//deltaTime = diff / 1000.0f;
		//lastTime = currentTime;
	}

}