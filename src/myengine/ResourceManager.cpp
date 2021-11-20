#include "ResourceManager.h"
#include "Core.h"

#include <memory>

namespace myengine
{
	/**
	* \brief Creates the resource manager.
	*
	* Once created, it stores itself alongside the core.
	*
	* \param _core Passes through the core and stores it.
	*/
	std::shared_ptr<ResourceManager> ResourceManager::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<ResourceManager> rtn = std::make_shared<ResourceManager>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;
		return rtn;
	}
}