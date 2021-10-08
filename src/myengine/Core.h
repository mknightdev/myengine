#include <memory>
#include <vector>

namespace myengine
{
	struct Entity;
	struct Environment;
	struct Keyboard;

	struct Core
	{
		static std::shared_ptr<Core> initialize();
		std::shared_ptr<Entity> addEntity();

		private:
			int dummy;
			bool running;
			std::vector<std::shared_ptr<Entity>> entities;
			std::shared_ptr<Environment> environment;
			std::shared_ptr<Keyboard> keyboard;
	};
}