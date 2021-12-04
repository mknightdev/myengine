#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	//mr->setMesh("../resources/models/grenade/grenade.obj");
	mr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/grenade/grenade"));
	// texture
	mr->setTexture(core->getResourceManager()->load<Texture>("resources/models/grenade/grenade_albedo"));
	// shader

	//std::shared_ptr<Entity> modelEntity = core->addEntity();
	//modelEntity->addComponent<ModelRenderer>();
	//modelEntity->getComponent<ModelRenderer>();

	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	// TODO
	// Create an engine texture that creates a myrenderer::Texture simiilar to Mesh
	// In the initialise function, add .png, .bitmap, .jpeg, etc and try for each
		// Audio would have .ogg in initiliase
	// take out "using namespace myrenderer" to avoid conflicts

	core->start();

	return 0;
}
