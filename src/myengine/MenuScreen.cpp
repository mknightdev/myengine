#include "MenuScreen.h"
#include "Core.h"
#include "Button.h"

#include <iostream>
#include <stb_image.h>

namespace myengine
{
	void MenuScreen::onInitialize()
	{
		// Load icons and models
		std::cout << "MenuScreen initialised" << std::endl;

		//std::shared_ptr<Entity> eButton = getCore()->addEntity();
		//std::shared_ptr<Button> cButton = eButton->addComponent<Button>();
		//cButton->setTexture("resources/textures/test.png");
		//cButton->setShader("resources/shaders/uiVert.txt", "resources/shaders/uiFrag.txt");

		std::shared_ptr<Entity> camEntity = getCore()->addEntity("Camera");
		std::shared_ptr<Camera> camComp = camEntity->addComponent<Camera>();

		camComp->setMove(false);

		// Menu Screen
		std::shared_ptr<Entity> eTitle = getCore()->addEntity();
		std::shared_ptr<MeshRenderer> cTitle = eTitle->addComponent<MeshRenderer>();
		cTitle->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/icons/menu"));
		cTitle->setTexture(getCore()->getResourceManager()->load<Texture>(""));
		cTitle->getTransform()->setPosition(vec3(-3, 1, -3));


		// Text
		std::shared_ptr<Entity> eText = getCore()->addEntity();
		std::shared_ptr<MeshRenderer> cText = eText->addComponent<MeshRenderer>();
		cText->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/icons/start"));
		cText->setTexture(getCore()->getResourceManager()->load<Texture>(""));
		cText->getTransform()->setPosition(vec3(-3.75, -1, -3));
		cText->getTransform()->setScale(vec3(0.35f, 0.35f, 0.35f));

		// Menu Music
		std::shared_ptr<SoundSource> ss = eTitle->addComponent<SoundSource>();
		ss->setSound(getCore()->getResourceManager()->load<Sound>("resources/sounds/menu"));
		ss->SetVolume(0.15);
		ss->SetLooping(true);
		ss->Play();
	}

	void MenuScreen::onDisplay()
	{

	}

	void MenuScreen::onTick()
	{
		// TODO:
		// Add key check to swap to game scene
		if (getKeyDown(SDLK_s))
		{
			getCore()->clear();

			std::shared_ptr<Entity> eSceneOne = getCore()->addEntity();
			std::shared_ptr<SceneOne> cSceneOne = eSceneOne->addComponent<SceneOne>();
		}
	}
}