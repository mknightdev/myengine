//#include "Enemy.h"

#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	// PBR Screen #1
	std::shared_ptr<Entity> pbrEntity = core->addEntity();
	std::shared_ptr<PBRScreen> pbrScreen = pbrEntity->addComponent<PBRScreen>();

	//std::shared_ptr<Entity> mrEntity = core->addEntity();
	//std::shared_ptr<MeshRenderer> mr = mrEntity->addComponent<MeshRenderer>();
	//mr->setMesh(core->getResourceManager()->load<Mesh>("../resources/models/grenade/grenade"));
	//mr->setTexture(core->getResourceManager()->load<Texture>("../resources/models/grenade/grenade_albedo"));

	//std::shared_ptr<Entity> ee = core->addEntity();
	//std::shared_ptr<Enemy> ec = ee->addComponent<Enemy>();

	// PBR stuff 
	//rowTwo(core);

	core->start();

	return 0;
}