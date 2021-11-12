#include "Component.h"

#include <myrenderer/myrenderer.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
//#include <vector>

namespace myengine
{
	struct Core;

	struct TriangleRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		void mouseUpdate();

		private:
			friend struct myengine::Core;
			float rot;
			std::weak_ptr<Core> core;
			std::shared_ptr<myrenderer::ShaderProgram> triangleShader;
			std::shared_ptr<myrenderer::VertexArray> vao;
			std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
			std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;
			std::shared_ptr<myrenderer::Texture> texture;

			float deltaTime;
			unsigned int prevTime;
	};
}
