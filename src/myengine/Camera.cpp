#include "Camera.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <iostream>

namespace myengine
{
	std::shared_ptr<Camera> Camera::create(std::weak_ptr<Core> _core)
	{
		std::shared_ptr<Camera> rtn = std::make_shared<Camera>();
		rtn->self = rtn;
		rtn->core = _core;

		return rtn;
	}

	/**
	* \brief Initialises the Camera
	* 
	* Initialises the Camera to default values.
	*/
	void Camera::onInitialize()
	{
		std::cout << "Camera Init" << std::endl;

		firstMouse = true;
		yaw = -90.0f;
		pitch = 0.0f;
		lastX = 1280.0f / 2.0;
		lastY = 720.0f / 2.0;
		fov = 45.0f;
		cameraSpeed = 2.5f;

		cameraPos = vec3(0.0f, 0.0f, 3.0f);
		cameraFront = vec3(0.0f, 0.0f, -1.0f);
		cameraUp = vec3(0.0f, 1.0f, 0.0f);
	}

	void Camera::onDisplay() 
	{
	}

	/**
	* \brief Updates Camera Position
	* 
	* Updates Camera positions and detects for input to move the Camera around
	* 
	* \see mouseUpdate
	*/
	void Camera::onTick(float _deltaTime)
	{
		if (getKeyboard()->getKeyDown(SDLK_w))
		{
			cameraPos += cameraSpeed * cameraFront * _deltaTime;
		}

		if (getKeyboard()->getKeyDown(SDLK_s))
		{
			cameraPos -= cameraSpeed * cameraFront * _deltaTime;
		}

		if (getKeyboard()->getKeyDown(SDLK_a))
		{
			cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed * _deltaTime;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed * _deltaTime;
		}

		mouseUpdate();
	}

	/**
	* \brief Updates Mouse Coordinates
	* 
	* Updates the Mouse coordinates and is used when moving the Camera around the scene.
	* 
	* \see myengine::Mouse
	*/
	void Camera::mouseUpdate()
	{
		//std::cout << "CAM: mouseUpdate" << std::endl;
		if (firstMouse)
		{
			lastX = getMouse()->getMousePosition().x;
			lastY = getMouse()->getMousePosition().y;
			firstMouse = false;
		}

		float xOffset = getMouse()->getMousePosition().x - lastX;
		float yOffset = lastY - getMouse()->getMousePosition().y;	// Reversed since y-coordinates go from bottom to top
		lastX = getMouse()->getMousePosition().x;
		lastY = getMouse()->getMousePosition().y;

		float sensitivity = 0.1f;
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		yaw += xOffset;
		pitch += yOffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}

		vec3 front;
		front.x = cos(radians(yaw)) * cos(radians(pitch));
		front.y = sin(radians(pitch));
		front.z = sin(radians(yaw)) * cos(radians(pitch));
		cameraFront = normalize(front);
	}

	vec3 Camera::getCameraPos()
	{
		return cameraPos;
	}

	vec3 Camera::getCameraFront()
	{
		return cameraFront;
	}

	vec3 Camera::getCameraUp()
	{
		return cameraUp;
	}
}