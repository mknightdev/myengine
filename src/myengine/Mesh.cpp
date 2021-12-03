#include "Mesh.h"

namespace myengine
{
	void Mesh::onInitialize()
	{
		vao = std::make_shared<myrenderer::VertexArray>(GetPath() + ".obj");
	}
}