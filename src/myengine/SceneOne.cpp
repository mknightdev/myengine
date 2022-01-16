#include "SceneOne.h"
#include <myengine/myengine.h>

#include "demo/Player.h"
#include "demo/Coin.h"

#include <iostream>

namespace myengine
{
	void SceneOne::onInitialize()
	{
		std::cout << "SceneOne init" << std::endl;

		std::shared_ptr<Entity> camEntity = getCore()->addEntity("Camera");
		std::shared_ptr<Camera> camComp = camEntity->addComponent<Camera>();
		camComp->setMove(true);

		// Player
		std::shared_ptr<Entity> pe = getCore()->addEntity();
		std::shared_ptr<Player> pc = pe->addComponent<Player>();

		std::shared_ptr<Trigger> pt = pe->addComponent<Trigger>();
		std::shared_ptr<MeshRenderer> pmr = pe->addComponent<MeshRenderer>();
		pmr->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/croc/croc"));
		pmr->setTexture(getCore()->getResourceManager()->load<Texture>("resources/models/croc/croc_diffuse"));
		std::shared_ptr<SphereCollider> psc = pe->addComponent<SphereCollider>();
		std::shared_ptr<SoundSource> ss = pe->addComponent<SoundSource>();
		ss->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/doorbell2"));
		ss->SetVolume(0.25);
		ss->SetLooping(true);
		ss->Play();
		pmr->setRadius(3.0f);

		// Coin
		std::shared_ptr<Entity> ce = getCore()->addEntity();
		std::shared_ptr<Trigger> ct = ce->addComponent<Trigger>();
		std::shared_ptr<Coin> cc = ce->addComponent<Coin>();
		std::shared_ptr<MeshRenderer> cmr = ce->addComponent<MeshRenderer>();
		cmr->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/coin/coin"));
		cmr->setTexture(getCore()->getResourceManager()->load<Texture>("resources/models/coin/coin_diffuse"));
		cmr->setRadius(1.0f);
		std::shared_ptr<SphereCollider> sc = ce->addComponent<SphereCollider>();
		cmr->getTransform()->setPosition(vec3(0, 0, -5));

		// Coin 2
		std::shared_ptr<Entity> ce2 = getCore()->addEntity();
		std::shared_ptr<Trigger> ct2 = ce2->addComponent<Trigger>();
		std::shared_ptr<Coin> cc2 = ce2->addComponent<Coin>();
		std::shared_ptr<MeshRenderer> cmr2 = ce2->addComponent<MeshRenderer>();
		cmr2->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/coin/coin"));
		cmr2->setTexture(getCore()->getResourceManager()->load<Texture>("resources/models/coin/coin_diffuse"));
		cmr2->setRadius(1.0f);
		std::shared_ptr<SphereCollider> sc2 = ce2->addComponent<SphereCollider>();
		cmr2->getTransform()->setPosition(vec3(0, 0, -10));
	}
}