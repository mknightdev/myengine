#include <SDL2/SDL.h>
#include <AL/alc.h>

#include <memory>
#include <vector>

namespace myengine
{
	struct Entity;
	struct Environment;
	struct Keyboard;
	struct Mouse;

	/**
	* \brief This is the brief description. 
	* 
	* This is the detailed description.
	* 
	* \param _this This is a parameter.
	*/
	struct Core
	{
		/**
		* \brief Creates the core of the engine.
		*
		* The foundation of the game engine.
		* \warning If you don't call this function, the game engine won't work.
		*/
		static std::shared_ptr<Core> initialize();

		/**
		* \brief Initialises SDL Window.
		*
		* Initialises and creates an SDL Window that is 1280x720.
		*
		* \attention Will throw an exception if the window fails to create.
		*/
		void setupWindow();

		/**
		* \brief Initialises OpenGL.
		*
		* Initialises OpenGL and creates an OpenGL context for the window created.
		*
		* \attention Will throw an exception if the context fails to create and/or glew fails to initialise.
		*
		*/
		void setupGraphics();

		/**
		* \brief Initialises OpenAL soft.
		*
		* Sets the device and creates a context with the device.
		*
		* \attention Will throw an exception if the device fails, context fails,
		* or it fails to make the current context.
		*/
		void setupAudio();

		/**
		* \brief Starts the engine.
		* 
		* Creates the needed utilities and then starts the main loop of the engine.
		* It captures SDL poll events, including: SDL_Quit, SDL_MOUSEMOTION, SDL_KEYDOWN and SDL_KEYUP.
		* 
		* The environment->tick() function gets called to calculate deltatime. 
		* Then updates the world and display of the game engine by calling the tick and display function within Entity.
		*/
		void start();

		/**
		* \brief Stops the engine.
		* 
		* Stops the engine by setting the running boolean to false.
		*/
		void stop();

		/**
		* Adds an entity to the game engine. Components can then be attached to these entities.
		* Adds a transform component on creation. 
		*/
		std::shared_ptr<Entity> addEntity();

		/**
		* Gets and returns the keyboard created within the Core's initialisation.
		* 
		* \return std::shared_ptr<Keyboard> keyboard
		*/
		std::shared_ptr<Keyboard> getKeyboard();

		/**
		* Gets and returns the mouse created within the core's initialisation.
		* 
		* \return std::shared_ptr<Mouse> mouse
		*/
		std::shared_ptr<Mouse> getMouse();

		/**
		* Gets and returns the environment created within the core's initialize() function.
		* 
		* \return std::shared_ptr<Environment> environment
		*/
		std::shared_ptr<Environment> getEnvironment();

		private:
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::shared_ptr<Environment> environment;
			std::shared_ptr<Keyboard> keyboard;
			std::shared_ptr<Mouse> mouse;
			std::weak_ptr<Core> self;
			SDL_Window* window;
			ALCdevice* device;
			ALCcontext* context;
	};
}