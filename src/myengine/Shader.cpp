#include "Shader.h"

namespace myengine
{
	/**
	* Initialises the Shader
	*/
	void Shader::onInitialize()
	{
		shader = std::make_shared<myrenderer::ShaderProgram>();
	}
}