#include <memory>
#include <vector>

namespace myengine
{
	struct Core;
	struct Component;

	struct Entity
	{
		std::shared_ptr<Component> addComponent();

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->entity = self;
			components.push_back(rtn);
			return rtn;
		}

		std::shared_ptr<Core> getCore();

		private:
			friend struct myengine::Core;
			std::vector<std::shared_ptr<Component>> components;
			std::weak_ptr<Entity> self;
			std::weak_ptr<Core> core;
			void tick();
	};
}