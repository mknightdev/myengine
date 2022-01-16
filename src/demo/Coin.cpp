#include "Coin.h"
//#include "myengine/Component.h"

#include <myengine/myengine.h>

#include <iostream>

namespace myengine
{
	void Coin::onInitialize()
	{
		
		hasPlayed = false;
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

		std::shared_ptr<SoundSource> ss = getEntity()->addComponent<SoundSource>();
		ss->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/coin"));
		ss->SetVolume(0.25);
		ss->SetLooping(false);
		
		// Ensures the audio only plays once 
		if (!hasPlayed)
		{
			ss->Play();
			hasPlayed = true;
		}

		// Destroy
		//getEntity()->getComponent<SphereCollider>()->onDestroy();

		//onDestroy();
		//getEntity()->destroy = true;
	}


	void Coin::onDestroy()
	{
		std::cout << "Coin destroyed" << std::endl;
	}
}