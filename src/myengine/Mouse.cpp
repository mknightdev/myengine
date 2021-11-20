#include "Mouse.h"

namespace myengine
{
	/**
	* \brief Creates the mouse.
	*
	* Once created, it stores itself alongside the core.
	*
	* \param _core Passes through the core and stores it.
	*/
	std::shared_ptr<Mouse> Mouse::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Mouse> rtn = std::make_shared<Mouse>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;
		return rtn;
	}

	/**
	* \brief Returns the mouse position. 
	* 
	* Gets and returns the mouse position to be used for the camera, or UI elements.
	* 
	* \return mousePosition
	*/
	glm::vec2 Mouse::getMousePosition()
	{
		return mousePosition;
	}
}