#include "Coin.h"
//#include "myengine/Component.h"

#include <myengine/myengine.h>

#include <iostream>

namespace myengine
{
	void Coin::onInitialize()
	{
		audio = getEntity()->addComponent<SoundSource>();
		audio->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/coin"));
		audio->SetVolume(0.05);
		audio->SetLooping(false);

		hasPlayed = false;
	}

	void Coin::onDisplay()
	{
	}

	void Coin::onTick(float _deltaTime)
	{
		getTransform()->Rotate(vec3(0, 0.95f, 0) * _deltaTime);
	}

	void Coin::onTrigger()
	{
		// Ensures the audio only plays once 
		if (!hasPlayed)
		{
			audio->Play();
			hasPlayed = true;

			// Destroy
			//getEntity()->destroy = true;	// causes read access violation
		}
	}


	void Coin::onDestroy()
	{
		std::cout << "Coin destroyed" << std::endl;
	}
}