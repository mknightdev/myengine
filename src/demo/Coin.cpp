#include "Coin.h"
//#include "myengine/Component.h"

#include <myengine/myengine.h>

#include <iostream>

namespace myengine
{
	/// Initialises the coin object 
	void Coin::onInitialize()
	{
		audio = getEntity()->addComponent<SoundSource>();
		audio->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/coin"));
		audio->setVolume(0.05);
		audio->setLooping(false);

		hasPlayed = false;
	}

	/// Called each frame; Rotates the coin object. 
	void Coin::onTick(float _deltaTime)
	{
		getTransform()->Rotate(vec3(0, 0.95f, 0) * _deltaTime);
	}

	/**
	* \brief Trigger from Collision.
	* 
	* Call from Entity through to Component. Does something when a collision
	* is triggered. 
	* 
	* \see myengine::SphereCollider
	*/
	void Coin::onTrigger()
	{
		// Ensures the audio only plays once 
		if (!hasPlayed)
		{
			audio->play();
			hasPlayed = true;

			// Destroy
			//getEntity()->destroy = true;	// causes read access violation
		}
	}
}