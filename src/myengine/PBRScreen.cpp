#include "PBRScreen.h"
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
	void PBRScreen::onInitialize()
	{
		// Load icons and models
		std::cout << "PBRScreen Initialised" << std::endl;

		// ENTITY & COMPONENTS
		//====================
		sphereOne = getCore()->addEntity();
		std::shared_ptr<PBR> pbr = sphereOne->addComponent<PBR>();

		// BEATEN METAL SPHERE
		//====================
		pbr->setMesh(getCore()->getResourceManager()->load<Mesh>("../resources/models/sphere/sphere"));
		
		// SHADERS
		//========
		pbr->setShader("../resources/shaders/pbr/pbrTexVert.txt", "../resources/shaders/pbrFrag.txt");

		// MATERIAL VALUE
		//===============
		pbr->setAlbedo(vec3(1.0f, 0.0f, 0.0f));
		pbr->setMetallic(1.0f);
		pbr->setRoughness(0.1f);
		pbr->setAo(1.0f);



		pbr->getTransform()->setPosition(vec3(0, 0, -2.5f));
	}

	void PBRScreen::onTick(float _deltaTime)
	{
		////std::cout << "PBRScreen TICK" << std::endl;

		//if (getKeyboard()->getKeyDown(SDLK_RIGHT))
		//{
		//	std::cout << "Press LEFT ARROW to return to previous screen" << std::endl;

		//	// Clear the entiies ready for new screen
		//	getCore()->clear();

		//	std::shared_ptr<Entity> pbrEntity2 = getCore()->addEntity();
		//	std::shared_ptr<PBR2Screen> pbrScreen2 = pbrEntity2->addComponent<PBR2Screen>();
		//}
	}
}