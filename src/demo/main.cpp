#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;
using namespace myrenderer;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	mr->setMesh("../resources/models/grenade/grenade.obj");

	//std::shared_ptr<Entity> modelEntity = core->addEntity();
	//modelEntity->addComponent<ModelRenderer>();
	//modelEntity->getComponent<ModelRenderer>();

	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	core->start();

	return 0;
}
