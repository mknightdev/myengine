#pragma once

#include "Component.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct Mesh;
	struct Texture;

	struct PBRScreen : Component
	{
		void onInitialize();
		void onTick(float _deltaTime);	
	private:
		friend struct myengine::Core;
	};
}