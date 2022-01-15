#include "Trigger.h"
#include "SphereCollider.h"
#include "Entity.h"
#include "Core.h"

#include <iostream>

namespace myengine
{
	void Trigger::onTick(float _deltaTime)
	{
		// TODO: Cache into weak_ptr member variable
		std::shared_ptr<SphereCollider> sc = getEntity()->getComponent<SphereCollider>();

		std::vector<std::shared_ptr<SphereCollider>>& colliders = getCore()->colliders;

		for (size_t ci = 0; ci < colliders.size(); ++ci)
		{
			// Ignore collision against self
			if (colliders.at(ci) == sc) continue; 

			// If we collide, notify both parties
			if (sc->isColliding(colliders.at(ci)))
			{
				//std::cout << "Colliding" << std::endl;
				getEntity()->colliding(colliders.at(ci));
				colliders.at(ci)->getEntity()->colliding(sc);
			}
		}
	}
}