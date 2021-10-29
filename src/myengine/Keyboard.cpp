#include "Keyboard.h"

namespace myengine
{
	std::shared_ptr<Keyboard> Keyboard::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Keyboard> rtn = std::make_shared<Keyboard>();	// This becomes the instance
		rtn->self = rtn;
		rtn->core = _core;
		return rtn;
	}

	//bool Keyboard::getKey(int _keyCode)
	//{
	//	return false;
	//}

	bool Keyboard::getKeyDown(int _keyCode)
	{
		for (size_t i = 0; i < keyCodes.size(); i++)
		{
			if (_keyCode == keyCodes.at(i))
			{
				return true;
			}
		}
		return false;
	}

	bool Keyboard::getKeyUp(int _keyCode)
	{
		return _keyCode;
	}

	void Keyboard::removeKey(int _keyCode)
	{
		for (size_t i = 0; i < keyCodes.size(); i++)
		{
			if (_keyCode == keyCodes.at(i))
			{
				keyCodes.erase(keyCodes.begin() + i);
				i--;	//  Prevents skipping the element that's shuffled to its place
			}
		}
	}

	//std::shared_ptr<Core> Keyboard::getCore()
	//{
	//	return core.lock();	// .lock() converts the weak_ptr to a shared_ptr
	//}
}