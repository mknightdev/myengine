#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace myengine
{
	struct TriangleRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();

		//GLuint getId();

		//int getComponents();

		private:
			GLuint programId;
			GLuint vaoId;
			std::weak_ptr<Core> core;
	};
}