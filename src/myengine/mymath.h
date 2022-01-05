#ifndef MYENGINE_MATH_H
#define MYENGINE_MATH_H

#define GLM_FORCE_CTOR_INIT
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace myengine
{
	// Removes the need for 'glm::' within the game engine.
	using namespace glm;
}

#endif