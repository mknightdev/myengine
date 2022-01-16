#include "Component.h"

namespace myengine
{
	struct SphereCollider : Component
	{
		void onInitialize();
		void onDestroy();
		
		bool isColliding(std::shared_ptr<SphereCollider> _collider);

		float getRadius();

	private:

		/**
		* \brief Sphere Radius.
		* 
		* Used for determining collisions with other sphere colliders.
		*/
		float radius;
	};
}