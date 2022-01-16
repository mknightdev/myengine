#include "Coin.h"
//#include "myengine/Component.h"

#include <myengine/myengine.h>

#include <iostream>

namespace myengine
{
	void Coin::onInitialize()
	{
	}

	void Coin::onDisplay()
	{
	}

	void Coin::onTick(float _deltaTime)
	{
		getTransform()->Rotate(vec3(0, 0.5f, 0) * _deltaTime);
	}

	void Coin::onTick() {}

	void Coin::onTrigger()
	{
		std::cout << "[Coin] onTrigger" << std::endl;

		// If onTrigger was working as intended, a coin sound would play when there
		// is a collision with the coin indicating it has been picked up.

		std::shared_ptr<SoundSource> ss = getEntity()->addComponent<SoundSource>();
		ss->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/coin"));
		ss->SetVolume(0.25);
		ss->SetLooping(false);
		ss->Play();
	}


	void Coin::onDestroy()
	{
		std::cout << "Coin destroyed" << std::endl;
	}
}