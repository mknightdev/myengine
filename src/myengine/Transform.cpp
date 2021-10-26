#include "Transform.h"
#include <glm/glm.hpp>

#include <iostream>

namespace myengine
{
	void Transform::onInitialize()
	{
		std::cout << "Transform Initialized" << std::endl;

		scale = glm::vec3(1, 1, 1);
	}

	void Transform::setPosition(glm::vec3 _position)
	{
		position = _position;
	}

	void Transform::setRotation(glm::vec3 _rotation)
	{
		rotation = _rotation;
	}

	void Transform::setScale(glm::vec3 _scale)
	{
		scale = _scale;
	}

	glm::vec3 Transform::getScale()
	{
		return scale;
	}
}