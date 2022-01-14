#pragma once
#include "myengine/Component.h"

namespace myengine
{
	struct Player : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);
	};
}
