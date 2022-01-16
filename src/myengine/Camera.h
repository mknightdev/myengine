#include "Component.h"

#include "mymath.h"

namespace myengine
{
	struct Camera : Component
	{
		void onInitialize();
		void onTick(float _deltaTime);

		vec3 getCameraPos();
		vec3 getCameraFront();
		vec3 getCameraUp();

		void mouseUpdate();
		void setMove(bool state);

	private:
		friend struct myengine::Core;

		std::weak_ptr<Core> core;

		/**
		* \brief Camera Position.
		* 
		* Stores the position of the camera and can be retrieved elsewhere.
		* \see getCameraPos()
		*/
		vec3 cameraPos;

		/**
		* \brief Camera Front (Direction).
		* 
		* Stores the position of the front of the camera, used for its direction. Can be retrieved elsewhere.
		* \see getCameraFront()
		*/
		vec3 cameraFront;

		/**
		* \brief Camera Up (Direction).
		* 
		* Stores the position of camera up, used to determine which direction is up. Can be 
		* retrieved from elsewhere.
		* \see getCameraUp()
		*/
		vec3 cameraUp;

		/**
		* Used to check if first mouse movement.
		*/
		bool firstMouse;

		/**
		* \brief Camera Left & Right.
		* 
		* Used to set the limitations of the camera horizontally. 
		*/
		float yaw;

		/**
		* \brief Camera Up & Down.
		* 
		* Used to set the limitations of the camera vertically.
		*/
		float pitch;

		/**
		* \brief Last Position of Mouse X.
		*/
		float lastX; 

		/**
		* \brief Last Position of Mouse Y.
		*/
		float lastY;

		/**
		* \brief Determines how fast the Camera moves, i.e., sensitivity.
		*/
		float cameraSpeed;

		/**
		* \brief Determines movement
		*/
		bool canMove;
	};
}