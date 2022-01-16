#include "Entity.h"
#include "Component.h"
#include "SphereCollider.h"

#include "demo/Coin.h"

namespace myengine
{
	/**
	* Gets and returns the core of the engine.
	*
	* \return std::shared_ptr<Core> core
	*/
	std::shared_ptr<Core> Entity::getCore()
	{
		return core.lock();	// .lock() converts the weak_ptr to a shared_ptr
	}
	
	/**
	* \brief Draws OpenGL each loop.
	* 
	* Calls each display function within the entities in the game engine
	* and updates the OpenGL drawing.
	*/
	void Entity::display()
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->display();
		}
	}

	/**
	* \brief Updating the entity.
	*
	* The tick function within Entity iterates through its components and
	* calls the tick function to update themselves.
	*
	* \param _deltaTime Passes through the delta time calculated within the environment
	* and passed through the tick functions.
	*/
	void Entity::tick(float _deltaTime)
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->tick(_deltaTime);
		}
	}

	/**
	* \brief Calls the Trigger. 
	* 
	* Calls the trigger function within the component, to execute
	* the collision response.
	* 
	* \see myengine::Component
	*/ 
	void Entity::trigger()
	{
		for (size_t ei = 0; ei < components.size(); ++ei)
		{
			components.at(ei)->trigger();
		}
	}

	/**
	* \brief Colliding Notifier
	* 
	* Notifies the entity of the collision and then calls the required 
	* components to execute the response. 
	* 
	* \param _collider the collider that is colliding.
	* \see myengine::SphereCollider
	* \see trigger()
	*/
	void Entity::colliding(std::shared_ptr<SphereCollider> _collider)
	{
		_collider->getEntity()->trigger();
	}

	/**
	* Gets and returns the transform created when adding an entity.
	*
	* \return std::shared_ptr<Transform> transform.
	*/
	std::shared_ptr<Transform> Entity::getTransform()
	{
		return transform.lock();
	}
}