#include "myengine/Component.h"

namespace myengine
{
	struct Coin : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);
	};

}