#include "Core.h"
#include "Environment.h"

namespace myengine
{
	/**
	* \brief Creates the environment.
	* 
	* Once created, it stores itself alongside the core. 
	* It ensures deltaTime and currentTime and set to zero on creation. 
	* 
	* \param _core Passes through the core and stores it.
	*/
	std::shared_ptr<Environment> Environment::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Environment> rtn = std::make_shared<Environment>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;

		// Initialise to zero
		rtn->deltaTime = 0.0f;
		rtn->currentTime = 0.0f;

		return rtn;
	}

	/**
	* Gets and returns the deltaTime.
	*/
	float Environment::getDeltaTime()
	{
		return deltaTime;
	}

	/**
	* \brief Calculates deltaTime. 
	* 
	* Calculates deltaTime each frame by getting the current time and comparing
	* it with the last time.
	*
	* lastTime gets set at the end of each tick. 
	*/
	void Environment::tick()
	{
		currentTime = SDL_GetTicks();
		float diff = currentTime - lastTime;
		deltaTime = diff / 1000.0f;
		lastTime = currentTime;
	}
}