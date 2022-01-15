#pragma once

#include "Component.h"
#include "myrenderer/myrenderer.h"

namespace myengine
{
	struct MenuScreen : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();

	private:
		// store entities needed here
		friend struct myengine::Core;

		std::shared_ptr<myrenderer::ShaderProgram> shader;
		std::shared_ptr<myrenderer::VertexArray> vao;
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;
		std::shared_ptr<myrenderer::Texture> texture;
	};
}