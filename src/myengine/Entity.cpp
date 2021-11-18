#include "Entity.h"
#include "Component.h"

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
	* Gets and returns the transform created when adding an entity.
	*
	* \return std::shared_ptr<Transform> transform.
	*/
	std::shared_ptr<Transform> Entity::getTransform()
	{
		return transform.lock();
	}
}