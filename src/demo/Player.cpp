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
		if (getKeyDown(SDLK_UP))
		{
			getTransform()->Move(vec3(0, 0, 5) * _deltaTime);
		}

		if (getKeyDown(SDLK_DOWN))
		{
			getTransform()->Move(vec3(0, 0, -5) * _deltaTime);
		}

		//if (getKeyDown(SDLK_a))
		//{
		//	getTransform()->Move(vec3(5, 0, 0) * _deltaTime);
		//}

		//if (getKeyDown(SDLK_d))
		//{
		//	getTransform()->Move(vec3(-5, 0, 0) * _deltaTime);
		//}

		// Rotate Left
		if (getKeyDown(SDLK_LEFT))
		{
			getTransform()->Rotate(vec3(0, 1, 0) * _deltaTime);
		}

		// Rotate Right
		if (getKeyDown(SDLK_RIGHT))
		{
			getTransform()->Rotate(vec3(0, -1, 0) * _deltaTime);
		}
	}

	void Player::onTick() {}

	void Player::onTrigger()
	{
		std::cout << "Player Collision Triggered" << std::endl;
	}

	void Player::onDestroy() {}
}