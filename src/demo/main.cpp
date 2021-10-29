#include <myengine/myengine.h>
#include <myrenderer/myrenderer.h>

#include <iostream>

using namespace myengine;
using namespace myrenderer;

int main()
{
	std::shared_ptr<Core> core = Core::initialize();
	std::shared_ptr<Entity> entity = core->addEntity();

	entity->addComponent<TriangleRenderer>();
	entity->getComponent<TriangleRenderer>();

	core->start();

	return 0;
}
