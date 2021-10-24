#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;
using namespace myrenderer;

struct EngineStopper : Component
{
	void onTick()
	{
		std::cout << "Engine stopped" << std::endl;
		count++;
		if (count == 10)
		{
			getCore()->stop();
		}
	}

private:
	int count = 0;	// Add proper constructor, this is bad
};

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

	entity->addComponent<EngineStopper>();
	entity->getComponent<EngineStopper>();

	entity->addComponent<TriangleRenderer>();
	entity->getComponent<TriangleRenderer>();

	core->start();
	//core->stop();

	return 0;
}
