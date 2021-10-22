#include "TriangleRenderer.h"

#include <iostream>

namespace myengine
{
	void TriangleRenderer::onInitialize()
	{
		std::cout << "Triangle Initialised" << std::endl;

		// Create OpenGL vertex buffer, vertex array and shader capable of drawing a triangle
	}

	void TriangleRenderer::onDisplay()
	{
		std::cout << "Triangle Display" << std::endl;
	}

	void TriangleRenderer::onTick()
	{
		std::cout << "Triangle Tick" << std::endl;
	}
}