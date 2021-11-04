#include <memory>
#include <vector>
#include <iostream>

namespace myengine
{
	struct Core;
	struct Component;
	struct Transform;

	struct Entity
	{
		//std::shared_ptr<Component> addComponent();

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->entity = self;	// Sets the component entity as this
			components.push_back(rtn);
			rtn->onInitialize();	// Initialises the component
			return rtn;
		}
		
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t ci = 0; ci < components.size(); ci++)
			{
				// Check if the component matches the one we are trying to find
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));

				// If the component matches, return it 
				if (rtn)
				{
					std::cout << "Component match!" << std::endl;
					return rtn;
				}
			}
			throw std::exception();	// Early exit
		}

		std::shared_ptr<Core> getCore();
		std::shared_ptr<Transform> getTransform();

		private:
			friend struct myengine::Core;
			std::vector<std::shared_ptr<Component>> components;
			std::weak_ptr<Entity> self;
			std::weak_ptr<Core> core;
			std::weak_ptr<Transform> transform;
			void tick(float _deltaTime);
			void display();
	};
}
