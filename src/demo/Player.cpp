#include "Player.h"

#include <myengine/myengine.h>
#include <myengine/mymath.h>

#include <iostream>

namespace myengine
{
	void Player::onInitialize()
	{
		std::cout << "Custom Player Init" << std::endl;


	}

	void Player::onDisplay()
	{
		
	}

	void Player::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_k))
		{
			getTransform()->Move(vec3(0, 0, -5) * _deltaTime);
		}
	}
}