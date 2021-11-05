#include <memory>

namespace myengine
{
	struct Core;

	struct Environment
	{
		static std::shared_ptr<Environment> create(std::weak_ptr<Core> _core);
		float getDeltaTime();

		private:
			friend struct myengine::Core;
			float deltaTime;
			float lastTime;
			float currentTime;
			void tick();
			std::weak_ptr<Environment> self;
			std::weak_ptr<Core> core;

	};
}