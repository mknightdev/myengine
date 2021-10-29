#include "Transform.h"
#include <glm/glm.hpp>

#include <iostream>
#include <glm/ext.hpp>

namespace myengine
{
	void Transform::onInitialize()
	{
		std::cout << "Transform Initialized" << std::endl;

		position = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
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

	glm::mat4 Transform::getModel()
	{
		// Generate a new Matrix 4x4
		//model = glm::mat4(
		//	position.x, position.y, position.z, 0,
		//	rotation.x, rotation.y, rotation.z, 0,
		//	scale.x, scale.y, scale.z, 0,
		//	0, 0, 0, 1
		//);

		glm::mat4 rtn(1.0f);
		rtn = glm::translate(rtn, position);
		rtn = glm::rotate(rtn, rotation.x, glm::vec3(1, 0, 0));
		rtn = glm::rotate(rtn, rotation.y, glm::vec3(0, 1, 0));
		rtn = glm::rotate(rtn, rotation.z, glm::vec3(0, 0, 1));
		rtn = glm::scale(rtn, scale);

		return rtn;
	}
}