#include <exception>
#include <string>

#ifndef Exception_H
#define Exception_H

namespace myengine
{
	class Exception : public std::exception
	{
	public:
		Exception(std::string _message);
		~Exception() = default;

		const char* what();

	private:
		std::string message;
	};
}

#endif