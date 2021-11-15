#include "Entity.h"
#include "Component.h"

namespace myengine
{
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();	// .lock() converts the weak_ptr to a shared_ptr
	}

	void Entity::tick(float _deltaTime)
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->tick(_deltaTime);
		}
	}

	void Entity::display()
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->display();
		}
	}

	std::shared_ptr<Transform> Entity::getTransform()
	{
		return transform.lock();
	}
}