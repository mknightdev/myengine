#pragma once

#include "Component.h"
#include "myrenderer/myrenderer.h"

namespace myengine
{
	struct SceneOne : Component
	{
		void onInitialize();

	private:
		std::shared_ptr<myrenderer::ShaderProgram> shader;
		std::shared_ptr<myrenderer::VertexArray> vao;
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;
		std::shared_ptr<myrenderer::Texture> texture;
	};
}