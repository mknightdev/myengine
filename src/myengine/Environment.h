#include <memory>

namespace myengine
{
	struct Core;

	struct Environment
	{
		static std::shared_ptr<Environment> create(std::weak_ptr<Core> _core);
		float getDeltaTime();
		virtual void onTick();


		private:
			friend struct myengine::Core;
			float deltaTime;
			void tick();
			std::weak_ptr<Environment> self;
			std::weak_ptr<Core> core;
	};
}