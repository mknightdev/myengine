#include "Component.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct ModelRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		void mouseUpdate();

	private:
		friend struct myengine::Core;
		float rot;
		std::weak_ptr<Core> core;
		std::shared_ptr<myrenderer::ShaderProgram> shader;
		std::shared_ptr<myrenderer::ShaderProgram> lightShader;
		std::shared_ptr<myrenderer::VertexArray> vao;
		std::shared_ptr<myrenderer::VertexArray> lightVao;
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;
		std::shared_ptr<myrenderer::Texture> texture;
	};
}