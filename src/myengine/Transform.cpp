#include "Transform.h"

namespace myengine
{
	void Transform::onInitialize()
	{
		m_position = vec3(0, 0, -2.5f);
		m_rotation = vec3(0, 0, 0);
		m_scale = vec3(1, 1, 1);
	}

	void Transform::setPosition(vec3 _position)
	{
		m_position = _position;
	}

	void Transform::setRotation(vec3 _rotation)
	{
		m_rotation = _rotation;
	}

	void Transform::setScale(vec3 _scale)
	{
		m_scale = _scale;
	}

	vec3 Transform::getScale()
	{
		return m_scale;
	}

	mat4 Transform::getModel()
	{
		mat4 rtn(1.0f);
		rtn = scale(rtn, m_scale);
		rtn = translate(rtn, m_position);
		rtn = rotate(rtn, m_rotation.x, vec3(1, 0, 0));
		rtn = rotate(rtn, m_rotation.y, vec3(0, 1, 0));
		rtn = rotate(rtn, m_rotation.z, vec3(0, 0, 1));

		return rtn;
	}

	void Transform::Move(vec3 _moveValue)
	{
		m_position += _moveValue;
	}

	void Transform::Rotate(vec3 _rotValue)
	{
		m_rotation += _rotValue;
	}
}