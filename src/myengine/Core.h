#include <SDL2/SDL.h>

#include <memory>
#include <vector>

namespace myengine
{
	struct Entity;
	struct Environment;
	struct Keyboard;

	struct Core
	{
		void start();
		void stop();
		static std::shared_ptr<Core> initialize();

		// Setup window
		void setupWindow();

		// Setup graphics
		void setupGraphics();

		std::shared_ptr<Entity> addEntity();

		private:
			int dummy;
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::shared_ptr<Environment> environment;
			std::shared_ptr<Keyboard> keyboard;
			std::weak_ptr<Core> self;
			SDL_Window* window;
	};
}