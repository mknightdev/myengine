#include "Player.h"
#include "Coin.h"

#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();

	// Main Menu
	std::shared_ptr<Entity> eMenu = core->addEntity("MainMenu");
	std::shared_ptr<MenuScreen> cMenu = eMenu->addComponent<MenuScreen>();

	// PBR Screen #1
	//std::shared_ptr<Entity> pbrEntity = core->addEntity();
	//std::shared_ptr<PBRScreen> pbrScreen = pbrEntity->addComponent<PBRScreen>();

	//std::shared_ptr<Entity> entity = core->addEntity();
	//std::shared_ptr<MeshRenderer> mr = entity->addComponent<MeshRenderer>();
	//mr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/skeleton/skeleton"));
	//mr->setTexture(core->getResourceManager()->load<Texture>("resources/models/skeleton/skeleton_diffuse"));
	//std::shared_ptr<SoundSource> ss = entity->addComponent<SoundSource>();
	//ss->SetVolume(0.25);
	//ss->SetLooping(true);
	//ss->Play();

	//core->getEntityByName("Camera");
	//std::shared_ptr<SphereCollider> sc = entity->addComponent<SphereCollider>();

	// TODO:
	// Sound loading, similar to mesh and texture



	// Start the engine
	core->start();

	return 0;
}