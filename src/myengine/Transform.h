#pragma once

#include "Component.h"
#include "mymath.h"

namespace myengine
{
	struct Transform : Component
	{
		void onInitialize();

		mat4 getModel();

		void setPosition(vec3 _position);
		void setRotation(vec3 _rotation);
		void setScale(vec3 _scale);

		void Move(float _moveValue);
		void Move(vec3 _moveValue);
		void Rotate(vec3 _rotValue);

		vec3 getScale();

	private:
		/**
		* \brief The oject's position. 
		* 
		* Used for storing and updating the object's position. 
		*/
		vec3 m_position;

		/**
		* \brief The object's rotation.
		* 
		* Used for storing and updating the object's rotation. 
		*/
		vec3 m_rotation;
		
		/**
		* \brief The object's scale. 
		* 
		* Used for storing and updating the object's scale. 
		*/
		vec3 m_scale;
	};
}