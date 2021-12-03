#include "Resource.h"

#include <iostream>

namespace myengine
{
	/**
	* Initialises the reosurce.
	*/
	void Resource::onInitialize()
	{
		std::cout << "Resource initialised" << std::endl;
	}

	std::string Resource::GetPath()
	{
		return path;
	}
}