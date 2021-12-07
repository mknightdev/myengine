#include "Shader.h"

namespace myengine
{
	void Shader::onInitialize()
	{
		shader = std::make_shared<myrenderer::ShaderProgram>();
	}
}