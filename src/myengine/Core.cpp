#include "Core.h"
#include "Entity.h"
#include "Environment.h"

#include <GL\glew.h>

namespace myengine
{
	void Core::start()
	{
		environment = Environment::create(self);

		running = true;
		while (running)
		{ 
			environment->tick();

			// Update world
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->tick();
			}

			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->display();
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
		rtn->setupGraphics();
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

		window = SDL_CreateWindow("My Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	}

	void Core::setupGraphics()
	{
		if (!SDL_GL_CreateContext(window))
		{
			throw std::exception();
		}

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}	
}