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

		/**
		* Used for storing the shader and retrieving its ID.
		* \see myrenderer::ShaderProgram
		*/
		std::shared_ptr<myrenderer::ShaderProgram> shader;
	};
}