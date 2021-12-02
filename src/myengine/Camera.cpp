#include "Camera.h"
#include "Transform.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace myengine
{
	void Camera::onInitialize()
	{
		firstMouse = true;
		yaw = -90.0f;
		pitch = 0.0f;
		lastX = 1280.0f / 2.0;
		lastY = 720.0f / 2.0;
		fov = 45.0f;
		cameraSpeed = 2.5f;
	}

	void Camera::onDisplay() {}

	void Camera::onTick(float _deltaTime)
	{
		cameraSpeed *= _deltaTime;

		if (getKeyboard()->getKeyDown(SDLK_w))
		{
			cameraPos += cameraSpeed * cameraFront;
		}

		if (getKeyboard()->getKeyDown(SDLK_s))
		{
			cameraPos -= cameraSpeed * cameraFront;
		}

		if (getKeyboard()->getKeyDown(SDLK_a))
		{
			cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		if (getKeyboard()->getKeyDown(SDLK_d))
		{
			cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		mouseUpdate();
	}

	void Camera::mouseUpdate()
	{
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
		pitch = yOffset;

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
}