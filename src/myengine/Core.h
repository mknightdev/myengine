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

	struct Core
	{
		void start();
		void stop();
		static std::shared_ptr<Core> initialize();

		// Setup window
		void setupWindow();

		// Setup graphics
		void setupGraphics();

		// Setup audio
		void setupAudio();

		std::shared_ptr<Entity> addEntity();

		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
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