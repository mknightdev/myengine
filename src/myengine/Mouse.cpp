#include "Mouse.h"

namespace myengine
{
	std::shared_ptr<Mouse> Mouse::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Mouse> rtn = std::make_shared<Mouse>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;
		return rtn;
	}

	glm::vec2 Mouse::getMousePosition()
	{
		return mousePosition;
	}
}