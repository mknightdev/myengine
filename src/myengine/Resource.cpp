#include "Resource.h"

#include <iostream>

namespace myengine
{
	/**
	* Initialises the Resource.
	*/
	void Resource::onInitialize()
	{
		std::cout << "Resource initialised" << std::endl;
	}

	/**
	* Returns the path of the Resource
	*/
	std::string Resource::GetPath()
	{
		return path;
	}
}