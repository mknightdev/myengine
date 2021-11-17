#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;
using namespace myrenderer;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	std::shared_ptr<Entity> entity = core->addEntity();
	std::shared_ptr<Entity> modelEntity = core->addEntity();

	modelEntity->addComponent<ModelRenderer>();
	modelEntity->getComponent<ModelRenderer>();

	entity->addComponent<TriangleRenderer>();
	entity->getComponent<TriangleRenderer>();

	entity->addComponent<SoundSource>();
	//entity->getComponent<SoundSource>()->PlaySound();

	//std::shared_ptr<AudioClip> s = core->getResourceManager()->load<AudioClip>("doorbell");

	core->start();

	return 0;
}
