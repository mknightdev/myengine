#include "Mesh.h"

namespace myengine
{
	/**
	* \brief Initialises the Mesh
	*
	* Initialises the mesh by getting the path and adding the .obj extension.
	*
	* \attenion Must be a .obj file, no other format is supported.
	* \warning Will throw an exception if no file with the tried extension can be found.
	*/
	void Mesh::onInitialize()
	{
		vao = std::make_shared<myrenderer::VertexArray>(GetPath() + ".obj");
	}
}