#include "Component.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace myengine
{
	struct TriangleRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();

		//// OpenGL Stuff
		//void add(glm::vec2 _value);
		//void add(glm::vec3 _value);
		//void add(glm::vec4 _value);

		//GLuint getId();

		//int getComponents();

		//private:
		//	GLuint id;
		//	std::vector<float> data;
		//	bool dirty; // Trigger lazy uploading
		//	int components;
	};
}