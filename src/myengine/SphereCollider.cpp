#include "SphereCollider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"

#include "mymath.h"

namespace myengine
{
	void SphereCollider::onInitialize()
	{
		// TODO: Obtain radius from assigned mesh
		m_radius = 5.0f;

		// Register collider
		getCore()->registerCollider(getEntity()->getComponent<SphereCollider>());
	}

	void SphereCollider::onDestroy()
	{
		// Unregister collider
		getCore()->unregisterCollider(getEntity()->getComponent<SphereCollider>());
	}

	bool SphereCollider::isColliding(std::shared_ptr<SphereCollider> _collider)
	{
		// Get the distance between this sphere and the other sphere
		// If the distance is less than the radius combined, then there is a collision
		float distance = length(getTransform()->getPosition() - _collider->getTransform()->getPosition());

		if (distance <= (m_radius + _collider->getRadius()))
		{
			// Normalized of Object A, subtract Object B. Unit vector for direction only
			//normalDirection = normalize(getTransform()->getPosition() - _collider->getTransform()->getPosition());
			return true;
		}
		
		return false;
	}

	float SphereCollider::getRadius()
	{
		return m_radius;
	}

	void SphereCollider::collisionResponse(std::shared_ptr<SphereCollider> _collider)
	{
		//std::cout << "Response" << std::endl;

		// Normalize of A and B. Unit Vector for Direction only
		vec3 normalDir = normalize(getTransform()->getPosition() - _collider->getTransform()->getPosition());
		vec3 v1Temp, v1, v2, v1x, v2x, v1y, v2y, v1z, v2z; 
	}
}