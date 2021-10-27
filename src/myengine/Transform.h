#include "Component.h"

#include <glm/glm.hpp>

namespace myengine
{
	struct Transform : Component
	{
		void onInitialize();
		glm::mat4 getModel();
		void setPosition(glm::vec3 _position);
		void setRotation(glm::vec3 _rotation);
		void setScale(glm::vec3 _scale);

		glm::vec3 getScale();

		private:
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale = glm::vec3(1, 1, 1);
	};
}