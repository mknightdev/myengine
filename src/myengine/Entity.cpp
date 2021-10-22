#include "Entity.h"
#include "Component.h"
#include "Core.h"

namespace myengine
{
	std::shared_ptr<Component> Entity::addComponent()
	{
		std::shared_ptr<Component> rtn = std::make_shared<Component>();

		rtn->entity = self;
		components.push_back(rtn);

		return rtn;
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();	// .lock() converts the weak_ptr to a shared_ptr
	}

	void Entity::tick()
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->tick();
		}
	}

	void Entity::display()
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->display();
		}
	}
}