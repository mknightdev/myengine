#pragma once

#include "Component.h"
#include "myrenderer/myrenderer.h"

namespace myengine
{
	struct MenuScreen : Component
	{
		void onInitialize();
		void onTick();
	};
}