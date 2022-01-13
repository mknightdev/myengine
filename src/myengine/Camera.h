#include "Component.h"

#include "mymath.h"

namespace myengine
{
	struct Camera : Component
	{
		static std::shared_ptr<Camera> create(std::weak_ptr<Core> _core);

		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		vec3 getCameraPos();
		vec3 getCameraFront();
		vec3 getCameraUp();

		void mouseUpdate();

	private:
		friend struct myengine::Core;

		std::weak_ptr<Camera> self;
		std::weak_ptr<Core> core;

		vec3 cameraPos;
		vec3 cameraFront;
		vec3 cameraUp;

		/**
		* Used to check if first mouse movement.
		*/
		bool firstMouse;
		float yaw;
		float pitch;
		float lastX; 
		float lastY;
		float fov;

		/**
		* Determines how fast the Camera moves, i.e., sensitivity.
		*/
		float cameraSpeed;
	};
}