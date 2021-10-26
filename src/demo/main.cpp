#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;
using namespace myrenderer;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> entity = core->addEntity();
	//std::shared_ptr<Component> component = entity->addComponent();

	entity->getCore();
	///component->getCore();
	
	// Test parent back references
	std::cout << "Entity getCore(): " << entity->getCore() << std::endl;
	//std::cout << "Component getCore(): " << component->getCore() << std::endl;
	//std::cout << "Component getEntity(): " << component->getEntity() << std::endl;

	entity->addComponent<TriangleRenderer>();
	entity->getComponent<TriangleRenderer>();

	core->start();
	//core->stop();

	return 0;
}
