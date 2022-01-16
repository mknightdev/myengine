#include "Component.h"

namespace myengine
{
	struct SphereCollider : Component
	{
		void onInitialize();
		void onTrigger();
		void onDestroy();
		
		bool isColliding(std::shared_ptr<SphereCollider> _collider);

		float getRadius();

	private:
		float radius;
	};
}