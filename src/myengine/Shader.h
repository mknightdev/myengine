#include "Resource.h"
#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct MeshRenderer;

	struct Shader : Resource
	{
		void onInitialize();

	private:
		friend struct myengine::MeshRenderer;
		std::shared_ptr<myrenderer::ShaderProgram> shader;
	};
}