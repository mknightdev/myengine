#include "Resource.h"
#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct MeshRenderer;

	struct Mesh : Resource
	{
		void onInitialize();

	private:
		friend struct myengine::MeshRenderer;
		std::shared_ptr<myrenderer::VertexArray> vao;
	};
}