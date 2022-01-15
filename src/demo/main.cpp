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

	std::shared_ptr<Entity> camEntity = core->addEntity("Camera");
	std::shared_ptr<Camera> camComp = camEntity->addComponent<Camera>();

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

	//// Player
	//std::shared_ptr<Entity> pe = core->addEntity();
	//std::shared_ptr<Player> pc = pe->addComponent<Player>();
	//std::shared_ptr<SphereCollider> psc = pe->addComponent<SphereCollider>();
	//std::shared_ptr<Trigger> pt = pe->addComponent<Trigger>();
	//std::shared_ptr<MeshRenderer> pmr = pe->addComponent<MeshRenderer>();
	//pmr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/croc/croc"));
	//pmr->setTexture(core->getResourceManager()->load<Texture>("resources/models/croc/croc_diffuse"));
	//std::shared_ptr<SoundSource> ss = pe->addComponent<SoundSource>();
	//// Load in file
	//ss->setSound(core->getResourceManager()->load<Sound>("resources/sounds/doorbell2"));
	//ss->SetVolume(0.25);
	//ss->SetLooping(true);
	//ss->Play();

	//// Coin
	//std::shared_ptr<Entity> ce = core->addEntity();
	//std::shared_ptr<SphereCollider> sc = ce->addComponent<SphereCollider>();
	//std::shared_ptr<Trigger> ct = ce->addComponent<Trigger>();
	//std::shared_ptr<Coin> cc = ce->addComponent<Coin>();
	//std::shared_ptr<MeshRenderer> cmr = ce->addComponent<MeshRenderer>();
	//cmr->setMesh(core->getResourceManager()->load<Mesh>("resources/models/coin/coin"));
	//cmr->setTexture(core->getResourceManager()->load<Texture>("resources/models/coin/coin_albedo"));

	// Start the engine
	core->start();

	return 0;
}