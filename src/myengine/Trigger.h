#include "Component.h"

namespace myengine
{
	struct Trigger : Component
	{
		void onTick(float _deltaTime);
	};
}