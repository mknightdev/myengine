#include "Exception.h"

#include <iostream>

namespace myengine
{
	const char* Exception::what()
	{
		return message.c_str();
	}

	Exception::Exception(std::string _message)
	{
		std::cout << "Myengine Exception: " << _message << std::endl;
	}
}