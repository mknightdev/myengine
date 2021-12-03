#include "Resource.h"
#include "myrenderer/myrenderer.h"

namespace myengine
{
	struct MeshRenderer;

	struct Texture : Resource
	{
		void onInitialize();

	private:
		friend struct myengine::MeshRenderer;
		std::shared_ptr<myrenderer::Texture> texture;
	};
}