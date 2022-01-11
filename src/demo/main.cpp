//#include "Enemy.h"

#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	// PBR Screen #1
	//std::shared_ptr<Entity> pbrEntity = core->addEntity();
	//std::shared_ptr<PBRScreen> pbrScreen = pbrEntity->addComponent<PBRScreen>();

	std::shared_ptr<Entity> mrEntity = core->addEntity();
	std::shared_ptr<MeshRenderer> mr = mrEntity->addComponent<MeshRenderer>();
	mr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/skeleton/skeleton"));
	mr->setTexture(core->getResourceManager()->load<Texture>("resources/models/skeleton/skeleton_diffuse"));

	std::shared_ptr<Entity> croc = core->addEntity();
	std::shared_ptr<MeshRenderer> crocMr = croc->addComponent<MeshRenderer>();
	crocMr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/croc/croc"));
	crocMr->setTexture(core->getResourceManager()->load<Texture>("resources/models/croc/croc_diffuse"));
	std::shared_ptr<SoundSource> crocSs = croc->addComponent<SoundSource>();
	crocSs->SetVolume(0.25);
	crocSs->SetListener(0, 0, 0);
	crocSs->SetPosition(25, 0, 0);
	crocSs->SetLooping(true);
	crocSs->Play();

	// TODO:
	// Sound loading, similar to mesh and texture

	croc->getTransform()->setPosition(vec3(25, 0, 0));

	//mr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	//mr->setTexture(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));

	//std::shared_ptr<Entity> ee = core->addEntity();
	//std::shared_ptr<Enemy> ec = ee->addComponent<Enemy>();

	// Start the engine
	core->start();

	return 0;
}