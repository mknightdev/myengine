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

		std::shared_ptr<Entity> eButton = getCore()->addEntity();
		std::shared_ptr<Button> cButton = eButton->addComponent<Button>();
		//cButton->setTexture("resources/textures/test.png");
		//cButton->setShader("resources/shaders/uiVert.txt", "resources/shaders/uiFrag.txt");

	}

	void MenuScreen::onDisplay()
	{

	}

	void MenuScreen::onTick()
	{
		// TODO:
		// Add key check to swap to game scene
	}
}