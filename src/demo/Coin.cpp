#include "Coin.h"
#include <myengine/myengine.h>

#include <iostream>

namespace myengine
{
	void Coin::onInitialize()
	{
		std::cout << "Coin init" << std::endl;
	}

	void Coin::onDisplay()
	{
		std::cout << "[Coin] onDisplay" << std::endl;
	}

	void Coin::onTick(float _deltaTime)
	{
		std::cout << "[Coin] onTick" << std::endl;
		getTransform()->Rotate(vec3(0, 0.25f, 0) * _deltaTime);
	}

	void Coin::onTick() {}

	void Coin::onTrigger()
	{
		std::cout << "[Coin] onTrigger" << std::endl;
	}

	void Coin::onDestroy()
	{
		std::cout << "Coin destroyed" << std::endl;
	}
}