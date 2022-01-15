#include "Component.h"
#include <myrenderer/myrenderer.h>
#include <myengine/myengine.h>

namespace myengine
{
	struct Button : Component
	{
		void onInitialize();
		void onDisplay();
		void onTick();
		void onTick(float _deltaTime);

		// Button Properties
		void setTexture(std::string _fileName);
		void setShader(const GLchar* _vert, const GLchar* _frag);

		// Button Interaction
		bool intersect(vec2 _mouse, vec4 _rectangle);

	private:
		std::shared_ptr<myrenderer::ShaderProgram> shader;
		std::shared_ptr<myrenderer::VertexArray> vao;
		std::shared_ptr<myrenderer::VertexBuffer> positionsVbo;
		std::shared_ptr<myrenderer::VertexBuffer> texturesVbo;
		std::shared_ptr<myrenderer::Texture> texture;
	};
}