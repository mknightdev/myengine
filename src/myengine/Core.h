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
	struct ResourceManager;

	/**
	* \brief This is the brief description. 
	* 
	* This is the detailed description.
	* 
	* \param _this This is a parameter.
	*/
	struct Core
	{
		static std::shared_ptr<Core> initialize();

		void setupEngine();
		void setupWindow();
		void setupGraphics();
		void setupAudio();
		void start();
		void stop();

		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<ResourceManager> getResourceManager();

		private:

			/**
			* Can start or stop the engine depending on it's state. It gets set to true within the start() function,
			* and set to false within the stop() function.
			*/
			bool running;

			/**
			* \brief Stores entities.
			* 
			* Each entity that is created gets stored within entities.
			*/
			std::vector<std::shared_ptr<Entity>> entities;

			/**
			* Used for storing and updating deltaTime and retreiving delta time.
			*/
			std::shared_ptr<Environment> environment;

			/**
			* Used for storing and determing if a key has been pressed and released.
			*/
			std::shared_ptr<Keyboard> keyboard;

			/**
			* Used for storing and getting the user's mouse position.
			*/
			std::shared_ptr<Mouse> mouse;

			/**
			* Used for storing and loading resources within the engine.
			*/
			std::shared_ptr<ResourceManager> resourceManager;

			/**
			* Used for storing itself, and granting other classes to retrieve other 
			* components of the engine. 
			*/
			std::weak_ptr<Core> self;

			/**
			* The window created for SDL.
			*/
			SDL_Window* window;

			/**
			* The user's output device.
			*/
			ALCdevice* device;

			/**
			* The OpenAL soft context to link the device with.
			*/
			ALCcontext* context;
	};
}