#include "Core.h"
#include "Entity.h"
#include <SDL2/SDL.h>

namespace myengine
{
	void Core::start()
	{
		running = true;
		while (running)
		{ 
			// Update world
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->tick();
			}
		}

		// Render world
		// Post-render world
	}

	void Core::stop()
	{
		running = false;
	}

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;
		rtn->setupWindow();
		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity()
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();
		rtn->core = self;
		rtn->self = rtn;
		entities.push_back(rtn);

		return rtn;
	}

	void Core::setupWindow()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}
	}
}