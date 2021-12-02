#include "Component.h"

#include <myengine/mymath.h>

namespace myengine
{
	struct Camera : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		void mouseUpdate();

	private:
		vec3 cameraPos;
		vec3 cameraFront;
		vec3 cameraUp;

		bool firstMouse;
		float yaw;
		float pitch;
		float lastX; 
		float lastY;
		float fov; 
		float cameraSpeed;
	};
}