#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <AL/al.h>
#include <GL/glew.h>

namespace myengine
{
	void Core::setupWindow()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw std::exception();
		}

		window = SDL_CreateWindow("My Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
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

		std::cout << "INFO: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

		std::cout << "INFO: OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "INFO: OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "INFO: OpenGL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n" << std::endl;

		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
	}

	void Core::setupAudio()
	{
		device = alcOpenDevice(NULL);

		if (!device)
		{
			throw std::exception();
		}

		context = alcCreateContext(device, NULL);

		if (!context)
		{
			alcCloseDevice(device);
			throw std::exception();
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::exception();
		}
	}

	void Core::start()
	{
		environment = Environment::create(self);
		keyboard = Keyboard::create(self);
		mouse = Mouse::create(self);

		SDL_CaptureMouse(SDL_TRUE);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);

		running = true;
		while (running)
		{ 
			SDL_Event event = { 0 };

			// Do SDL event loop
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					std::cout << "Quit program!" << std::endl;
					running = false;
				}
				else if (event.type == SDL_MOUSEMOTION)
				{
					// Keep track of mouse position
					mouse->mousePosition = glm::vec2(event.motion.x, event.motion.y);

					//std::cout << "Mouse = (" << mouse->mousePosition.x << ", " << mouse->mousePosition.y << ")" << std::endl;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					keyboard->keyCodes.push_back(event.key.keysym.sym);
				}
				else if (event.type == SDL_KEYUP)
				{
					keyboard->removeKey(event.key.keysym.sym);
				}
				
				//switch (event.key.keysym.sym)
				//{
				//	case SDLK_ESCAPE: 
				//		std::cout << "Quit program with ESC!" << std::endl;
				//		running = false;
				//		SDL_DestroyWindow(window);
				//		SDL_Quit();
				//		break;
				//}
			}

			environment->tick();

			// Update world
			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->tick(environment->getDeltaTime());
			}

			glClear(GL_COLOR_BUFFER_BIT);

			for (size_t ei = 0; ei < entities.size(); ++ei)
			{
				entities.at(ei)->display();
				glDisable(GL_DEPTH_TEST);
			}

			//std::cout << "Delta: " << environment->getDeltaTime() << std::endl;

			SDL_GL_SwapWindow(window);

			// 0 to disable, 1 to enable, -1 for adaptive vsync
			SDL_GL_SetSwapInterval(0);
		}


		// Render world
		// Post-render world
	}

	void Core::stop()
	{
		// Close after use
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);

		// Stop the engine
		running = false;
	}

	std::shared_ptr<Core> Core::initialize()
	{
		std::shared_ptr<Core> rtn = std::make_shared<Core>();
		rtn->self = rtn;

		rtn->setupWindow();
		rtn->setupGraphics();
		rtn->setupAudio();
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

	std::shared_ptr<Mouse> Core::getMouse()
	{
		return mouse;
	}

	std::shared_ptr<Environment> Core::getEnvironment()
	{
		return environment;
	}

	std::shared_ptr<Resource> Core::getResources()
	{
		return resources;
	}
}
