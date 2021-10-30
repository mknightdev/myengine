#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include "Transform.h"
#include "Keyboard.h"

#include <GL/glew.h>

namespace myengine
{
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
	}

	void Core::start()
	{
		environment = Environment::create(self);
		keyboard = Keyboard::create(self);
	
		running = true;
		while (running)
		{ 
			SDL_Event event = { 0 };

			// Do SDL event loop
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					keyboard->keyCodes.push_back(event.key.keysym.sym);
					//if (keyboard->getKeyDown(event.key.keysym.sym))
					{
						std::cout << "Key pressed" << event.key.keysym.sym << std::endl;
					}

				}
				else if (event.type == SDL_KEYUP)
				{
					keyboard->removeKey(event.key.keysym.sym);
					//if (keyboard->getKeyUp(event.key.keysym.sym))
					{
						std::cout << "Key released" << std::endl;
					}
				}
			}

			environment->tick();

			// Update world
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->tick();
			}

			// TODO: Move to before display
			glClear(GL_COLOR_BUFFER_BIT);

			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->display();
			}

			// End time
			float currentTime = SDL_GetTicks();
			environment->setCurrentTime(currentTime);

			std::cout << "Delta: " << environment->getDeltaTime() << std::endl;

			SDL_GL_SwapWindow(window);
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
		rtn->transform = rtn->addComponent<Transform>();	// Form of caching and is faster than getComponent<T>

		entities.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Keyboard> Core::getKeyboard()
	{
		return keyboard;
	}
}
