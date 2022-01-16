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
	//std::shared_ptr<Entity> eMenu = core->addEntity("MainMenu");
	//std::shared_ptr<MenuScreen> cMenu = eMenu->addComponent<MenuScreen>();

	std::shared_ptr<Entity> eSceneOne = core->addEntity();
	std::shared_ptr<SceneOne> cSceneOne = eSceneOne->addComponent<SceneOne>();

	// Start the engine
	core->start();

	return 0;
}