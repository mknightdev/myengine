#include "Camera.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Mouse.h"

#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>

namespace myengine
{
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
		cameraSpeed = 2.5f;

		cameraPos = vec3(0.0f, 0.0f, 3.0f);
		cameraFront = vec3(0.0f, 0.0f, -1.0f);
		cameraUp = vec3(0.0f, 1.0f, 0.0f);
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
		// Update the listener position to where we are in the scene
		alListener3f(AL_POSITION, cameraPos.x, cameraPos.y, cameraPos.z);
		
		if (canMove)
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

	/**
	* \brief Returns the Camera Position.
	* 
	* \see cameraPos
	*/
	vec3 Camera::getCameraPos()
	{
		return cameraPos;
	}

	/**
	* \brief Returns the Camera Front Position.
	* 
	* \see cameraFront
	*/
	vec3 Camera::getCameraFront()
	{
		return cameraFront;
	}

	/**
	* \brief Returns the Camera Up Position.
	* 
	* \see cameraUp
	*/
	vec3 Camera::getCameraUp()
	{
		return cameraUp;
	}

	void Camera::setMove(bool state)
	{
		canMove = state;
	}
}