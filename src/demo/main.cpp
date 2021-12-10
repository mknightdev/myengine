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

	//std::shared_ptr<Entity> ee = core->addEntity();
	//std::shared_ptr<Enemy> ec = ee->addComponent<Enemy>();

	// PBR stuff 
	//rowTwo(core);

	// TODO
	// Create an engine texture that creates a myrenderer::Texture simiilar to Mesh
	// In the initialise function, add .png, .bitmap, .jpeg, etc and try for each
		// Audio would have .ogg in initiliase
	// take out "using namespace myrenderer" to avoid conflicts

	core->start();

	return 0;
}


