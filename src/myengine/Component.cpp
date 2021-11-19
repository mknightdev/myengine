#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include "Environment.h"

namespace myengine
{
	void Component::onTick(float _deltaTime) {}
	void Component::onDisplay() {}
	void Component::onInitialize() {}

	/**
	* Calls the onTick() function on all derived classes.
	* 
	* \param _deltaTime Passses through delta time to the derived classes.
	*/
	void Component::tick(float _deltaTime)
	{
		onTick(_deltaTime);
	}

	/**
	* Calls the onDisplay() function on all derived classes.
	*/
	void Component::display()
	{
		onDisplay();
	}
	
	/**
	* \brief Returns the Core.
	* 
	* Goes up the hierarchy, by going through the Entity, and returns the Core.
	*/
	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

	/**
	* \brief Returns the Entity.
	* 
	* Grants access to Entity and returns it.
	*/
	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();	// Makes weakptr into a shared
	}

	/**
	* \brief Returns the Keyboard.
	* 
	* Goes up the hierarchy, by getting the Core, and then returning the Keyboard.
	*/
	std::shared_ptr<Keyboard> Component::getKeyboard()
	{
		return getCore()->getKeyboard();
	}

	/**
	* \brief Returns the Mouse.
	* 
	* Goes up the hierarchy, by getting the Core, and then returning the Mouse. 
	*/
	std::shared_ptr<Mouse> Component::getMouse()
	{
		return getCore()->getMouse();
	}

	/**
	* \brief Returns the Transform.
	* 
	* Goes up the hierarchy, by getting the Entity, and returning the Transform.
	*/
	std::shared_ptr<Transform> Component::getTransform()
	{
		return getEntity()->getTransform();
	}

	/**
	* \brief Returns the deltaTime.
	* 
	* Goes up the hierarchy, by getting the Environment through the Core, and returning the deltaTime.
	*/
	float Component::deltaTime()
	{
		return getCore()->getEnvironment()->getDeltaTime();
	}
}