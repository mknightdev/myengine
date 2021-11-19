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
			vec3 m_position;
			vec3 m_rotation;
			vec3 m_scale;
	};
}