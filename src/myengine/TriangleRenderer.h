#include "Component.h"

#include <myrenderer/myrenderer.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace myengine
{
	struct Keyboard;
	struct Core;

	struct TriangleRenderer : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick(float _deltaTime);

		//GLuint getId();

		//int getComponents();

		std::shared_ptr<Core> getCore();

		private:
			friend struct myengine::Core;
			float rot;
			std::weak_ptr<Core> core;
			std::shared_ptr<myrenderer::ShaderProgram> triangleShader;
			std::shared_ptr<myrenderer::VertexArray> vao;
			std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
			glm::mat4 triangleModel;
	};
}
