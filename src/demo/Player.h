#include <myengine/Component.h>
#include <myengine/Trigger.h>

namespace myengine
{
	struct Player : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);
		void onTrigger();
		void onDestroy();
	};
}
