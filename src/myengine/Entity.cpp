#include "Entity.h"
#include "Component.h"

namespace myengine
{
	std::shared_ptr<Component> Entity::addComponent()
	{
		std::shared_ptr<Component> rtn = std::make_shared<Component>();
		components.push_back(rtn);

		return rtn;
	}
}