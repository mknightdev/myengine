#include <exception>
#include <string>

#ifndef Exception_H
#define Exception_H

namespace myengine
{
	struct Exception : public std::exception
	{
	public:
		Exception(const std::string _message) : message(_message) {};

		virtual ~Exception() throw() {};

		//const char* what();

		virtual const char* what() const throw()
		{
			return message.c_str();
		}

	private:

		/**
		* Used for showing the explanation of the error.
		*/
		std::string message;
	};
}

#endif