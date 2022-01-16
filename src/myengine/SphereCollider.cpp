#include "SphereCollider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "MeshRenderer.h"

#include "demo/Coin.h"
#include "mymath.h"

#include <iostream>

namespace myengine
{
	/**
	* \brief Initialises the Sphere Collider.
	* 
	* Initialises the Sphere Collider by getting the radius 
	* and registering the collider with the engine. 
	* 
	* \see Core::registerCollider()
	*/
	void SphereCollider::onInitialize()
	{
		radius = getEntity()->getComponent<MeshRenderer>()->getRadius();
		
		// Register collider
		getCore()->registerCollider(getEntity()->getComponent<SphereCollider>());
	}

	/**
	* \brief Destroys the Collider.
	* 
	* When called, it will unregister the collider from the engine, preventing
	* future collisions with other colliders.
	*/
	void SphereCollider::onDestroy()
	{
		// Unregister collider
		getCore()->unregisterCollider(getEntity()->getComponent<SphereCollider>());
	}

	/**
	* \brief Checks for Collisions.
	* 
	* Determines if two or more objects are colliding by getting the distance and checking if it collides. 
	* 
	* \return true if there is a collision.
	* \return false if there isn't a collision.
	*/
	bool SphereCollider::isColliding(std::shared_ptr<SphereCollider> _collider)
	{
		// Get the distance between this sphere and the other sphere
		// If the distance is less than the radius combined, then there is a collision
		float distance = length(getTransform()->getPosition() - _collider->getTransform()->getPosition());

		if (distance <= (radius + _collider->getRadius()))
		{
			// Normalized of Object A, subtract Object B. Unit vector for direction only
			//normalDirection = normalize(getTransform()->getPosition() - _collider->getTransform()->getPosition());
			return true;
		}
		
		return false;
	}

	/// Returns the Sphere Collider's radius.
	float SphereCollider::getRadius()
	{
		return radius;
	}
}