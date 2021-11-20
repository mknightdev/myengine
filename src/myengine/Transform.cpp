#include "Transform.h"

namespace myengine
{
	/**
	* \brief Initialises the Transform.
	*
	* Sets the initial values of m_position, m_rotation and m_scale.
	*/
	void Transform::onInitialize()
	{
		m_position = vec3(0, 0, -2.5f);
		m_rotation = vec3(0, 0, 0);
		m_scale = vec3(1, 1, 1);
	}

	/**
	* \brief Sets the position. 
	* 
	* Sets the position of the object to the new position provided. 
	* 
	* \param _position the vec3 to update the position with.
	*/
	void Transform::setPosition(vec3 _position)
	{
		m_position = _position;
	}

	/** 
	* \brief Sets the rotation. 
	* 
	* Sets the rotation of the object to the new rotation provided.
	* 
	* \param _rotation the vec3 to update the rotation with.
	*/
	void Transform::setRotation(vec3 _rotation)
	{
		m_rotation = _rotation;
	}

	/**
	* \brief Sets the scale. 
	* 
	* Sets the scale of the object to the new scale provided. 
	* 
	* \param _scale the vec3 to update the scale with.
	*/
	void Transform::setScale(vec3 _scale)
	{
		m_scale = _scale;
	}

	/**
	* \brief Gets the scale. 
	* 
	* \return m_scale the scale of the object. 
	*/
	vec3 Transform::getScale()
	{
		return m_scale;
	}

	/**
	* \brief Gets the model. 
	* 
	* Gets and returns the model matrix of the object. Includes scale, position and rotation. 
	* 
	* \return the model matrix of the object. 
	*/
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

	/**
	* \brief Moves the object.
	* 
	* Moves the object in the direction it is facing. 
	* 
	* \param _moveValue a float value for how much the model should move each tick. 
	* \attention This is the float version of Move(). 
	* \see Move(vec3 _moveValue)
	*/
	void Transform::Move(float _moveValue)
	{
		mat4 model = getModel();
		vec3 fwd = vec3(model * vec4(0, 0, 1, 0));
		m_position += fwd * _moveValue;
	}

	/**
	* \brief Moves the object.
	* 
	* Moves the object in the direction it is facing. 
	* 
	* \param _moveValue a vec3 value for how much the model should move each tick. 
	* \attention This is the vec3 version of Move(). 
	* \see Move(float _moveValue)
	*/
	void Transform::Move(vec3 _moveValue)
	{
		mat4 model = getModel();
		vec3 fwd = vec3(model * vec4(_moveValue, 0));
		m_position += fwd;
	}

	/** 
	* \brief Rotates the object.
	* 
	* Rotates the object using the parameter value. 
	* 
	* \param _rotValue the vec3 value for how much to rotate by. 
	*/
	void Transform::Rotate(vec3 _rotValue)
	{
		m_rotation += _rotValue;
	}
}