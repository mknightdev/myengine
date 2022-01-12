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


	//// TODO: Add Camera component
	//std::shared_ptr<Entity> camObj = core->addEntity();
	std::shared_ptr<Camera> cam1;

	std::shared_ptr<Entity> mrEntity = core->addEntity();
	std::shared_ptr<MeshRenderer> mr = mrEntity->addComponent<MeshRenderer>();
	std::shared_ptr<Camera> cam = mrEntity->addComponent<Camera>();
	mr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/skeleton/skeleton"));
	mr->setTexture(core->getResourceManager()->load<Texture>("resources/models/skeleton/skeleton_diffuse"));

	//std::shared_ptr<Entity> croc = core->addEntity();
	//std::shared_ptr<MeshRenderer> crocMr = croc->addComponent<MeshRenderer>();
	//crocMr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/croc/croc"));
	//crocMr->setTexture(core->getResourceManager()->load<Texture>("resources/models/croc/croc_diffuse"));
	//std::shared_ptr<SoundSource> crocSs = croc->addComponent<SoundSource>();
	//crocSs->SetVolume(0.25);
	//crocSs->SetListener(0, 0, 0);
	//crocSs->SetLooping(true);
	//crocSs->Play();

	//croc->getTransform()->setPosition(vec3(10, 0, 0));

	//std::shared_ptr<Entity> croc2 = core->addEntity();
	//std::shared_ptr<MeshRenderer> crocMr2 = croc2->addComponent<MeshRenderer>();
	//crocMr2->setMesh(core->getResourceManager()->load<Mesh>("resources/models/croc/croc"));
	//crocMr2->setTexture(core->getResourceManager()->load<Texture>("resources/models/croc/croc_diffuse"));
	//std::shared_ptr<SoundSource> crocSs2 = croc2->addComponent<SoundSource>();
	//crocSs2->SetVolume(0.25);
	//crocSs2->SetListener(0, 0, 0);
	//crocSs2->SetLooping(true);
	//crocSs2->Play();

	//croc2->getTransform()->setPosition(vec3(-10, 0, 0));


	// TODO:
	// Sound loading, similar to mesh and texture



	//mr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	//mr->setTexture(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));

	//std::shared_ptr<Entity> ee = core->addEntity();
	//std::shared_ptr<Enemy> ec = ee->addComponent<Enemy>();

	// Start the engine
	core->start();

	return 0;
}