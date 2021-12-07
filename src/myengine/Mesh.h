#include "Resource.h"
#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct MeshRenderer;
	struct PBR;

	struct Mesh : Resource
	{
		void onInitialize();

	private:
		friend struct myengine::MeshRenderer;
		friend struct myengine::PBR;
		std::shared_ptr<myrenderer::VertexArray> vao;
	};
}