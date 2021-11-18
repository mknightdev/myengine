#include "Keyboard.h"

namespace myengine
{
	/**
	* \brief Creates the keyboard.
	* 
	* Once created, it stores itself alongside the core.
	* 
	* \param _core Passses through the core and stores it.
	*/
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

	/**
	* Detects if the key required is the key that has been pressed this SDL poll event.
	* 
	* \param _keyCode The key code to check against. 
	* \return True if it is the matching key code. If not, it will be false. 
	*/
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

	//bool Keyboard::getKeyUp(int _keyCode)
	//{
	//	return _keyCode;
	//}

	/**
	* \brief Removes the key that has been released.
	*
	* Iterates through the keyCodes that have been pressed and removes the matching one.
	* Prevents checking against keys that don't need to be checked against. 
	*
	* \param _keyCode The key code to remove.
	*/
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
}