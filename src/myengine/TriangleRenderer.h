#include "Component.h"

namespace myengine
{
	struct TriangleRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();
	};
}