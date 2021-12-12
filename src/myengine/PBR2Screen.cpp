#include "PBR2Screen.h"
#include "Transform.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "mymath.h"

#include <memory>
#include <SDL2/SDL.h>
#include <iostream>

#include "stb_image.h"
#include "GL\glew.h"

#include <myengine/myengine.h>

namespace myengine
{
	void PBR2Screen::onInitialize()
	{
		// Load icons and models
		std::cout << "PBRScreen Initialised" << std::endl;

		// ENTITY & COMPONENTS
		//====================
		std::shared_ptr<Entity> sphereOne = getCore()->addEntity();
		std::shared_ptr<PBR> pbr = sphereOne->addComponent<PBR>();

		// MESH & SHADER
		//====================
		pbr->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		// MATERIAL VALUE
		//===============
		pbr->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr->setMetallic(0.5f);
		pbr->setRoughness(0.0f);
		pbr->setAo(1.0f);

		pbr->getTransform()->setPosition(vec3(0, 0, -2.5f));

		std::shared_ptr<Entity> sphereTwo = getCore()->addEntity();
		std::shared_ptr<PBR> pbr2 = sphereTwo->addComponent<PBR>();

		pbr2->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr2->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		pbr2->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr2->setMetallic(1.0f);
		pbr2->setRoughness(0.0f);
		pbr2->setAo(1.0f);

		pbr2->getTransform()->setPosition(vec3(2, 0, -2.5f));

		std::shared_ptr<Entity> sphereThree = getCore()->addEntity();
		std::shared_ptr<PBR> pbr3 = sphereThree->addComponent<PBR>();

		pbr3->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr3->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		pbr3->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr3->setMetallic(0.25f);
		pbr3->setRoughness(0.0f);
		pbr3->setAo(1.0f);

		pbr3->getTransform()->setPosition(vec3(-2, 0, -2.5f));

		//===========
		// SECOND ROW
		//===========

		std::shared_ptr<Entity> sphereFour = getCore()->addEntity();
		std::shared_ptr<PBR> pbr4 = sphereFour->addComponent<PBR>();

		pbr4->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr4->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		pbr4->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr4->setMetallic(0.0f);
		pbr4->setRoughness(0.5f);
		pbr4->setAo(1.0f);

		pbr4->getTransform()->setPosition(vec3(0, 2, -2.5f));

		std::shared_ptr<Entity> sphereFive = getCore()->addEntity();
		std::shared_ptr<PBR> pbr5 = sphereFive->addComponent<PBR>();

		pbr5->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr5->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		pbr5->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr5->setMetallic(0.0f);
		pbr5->setRoughness(1.0f);
		pbr5->setAo(1.0f);

		pbr5->getTransform()->setPosition(vec3(2, 2, -2.5f));

		std::shared_ptr<Entity> sphereSix = getCore()->addEntity();
		std::shared_ptr<PBR> pbr6 = sphereSix->addComponent<PBR>();

		pbr6->setMesh(getCore()->getResourceManager()->load<Mesh>("resources/models/sphere/sphere"));
		pbr6->setShader("resources/shaders/pbr/pbrTexVert.txt", "resources/shaders/pbr/pbrTexFrag2.txt");

		pbr6->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr6->setMetallic(0.0f);
		pbr6->setRoughness(0.25f);
		pbr6->setAo(1.0f);

		pbr6->getTransform()->setPosition(vec3(-2, 2, -2.5f));
	}

	void PBR2Screen::onTick(float _deltaTime)
	{
		//std::cout << "PBRScreen TICK" << std::endl;

		if (getKeyboard()->getKeyDown(SDLK_LEFT))
		{
			std::cout << "Press RIGHT ARROW to return to previous screen" << std::endl;

			// Clear the entiies ready for new screen
			getCore()->clear();

			std::shared_ptr<Entity> pbrEntity = getCore()->addEntity();
			std::shared_ptr<PBRScreen> pbrScreen = pbrEntity->addComponent<PBRScreen>();
		}
	}
}