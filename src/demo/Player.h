#include <myengine/Component.h>
#include <myengine/Trigger.h>

namespace myengine
{
	struct Player : Component
	{
		void onTick(float _deltaTime);
	};
}
