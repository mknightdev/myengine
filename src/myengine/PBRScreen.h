#pragma once

#include "Component.h"

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