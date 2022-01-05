#pragma once

#include "Component.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct Mesh;
	struct Texture;

	struct PBR2Screen : Component
	{
		void onInitialize();
		void onTick(float _deltaTime);

	private:
		friend struct myengine::Core;

		// Store entities needed here
		std::shared_ptr<Entity> sphereOne;
		std::shared_ptr<Entity> sphereTwo;
		std::shared_ptr<Entity> sphereThree;
		std::shared_ptr<Entity> sphereFour;
	};
}