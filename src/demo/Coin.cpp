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

	}

	void Coin::onTick(float _deltaTime)
	{
		getTransform()->Rotate(vec3(0, 0.25f, 0) * _deltaTime);
	}
}