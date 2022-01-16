#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include "Environment.h"
#include "Transform.h"
#include "Camera.h"
#include "Keyboard.h"

#include "SoundSource.h"
#include "Sound.h"
#include "ResourceManager.h"

#include <iostream>
#include "mymath.h"

namespace myengine
{
	void Component::onInitialize() {}
	void Component::onDisplay() {}
	void Component::onTick(float _deltaTime) {}
	void Component::onTrigger() {}


	/**
	* \brief Calls the onTick() function on all derived classes.
	* 
	* \param _deltaTime Passses through delta time to the derived classes.
	* \see tick()
	*/
	void Component::tick(float _deltaTime)
	{
		onTick(_deltaTime);
	}

	/// Calls the onDisplay() function on all derived classes. 
	void Component::display()
	{
		onDisplay();
	}

	/// Calls the onTrigger() function on all derived classes. 
	void Component::trigger()
	{
		onTrigger();
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
	* \brief Shortcut for getKeyDown
	* 
	* Checks if the provided key has been pressed. 
	* 
	* \return true if it has.
	* \return false if it hasn't.
	*/
	bool Component::getKeyDown(int _keyCode)
	{
		return getKeyboard()->getKeyDown(_keyCode);
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
	* \brief setPosition shortcut.
	* 
	* Gets the transform and calls the setPosition member function.
	* 
	* \param _position the vec3 to update the position with.
	* \see myengine::Transform
	*/
	void Component::setPosition(vec3 _position)
	{
		getTransform()->setPosition(_position);
	}

	/**
	* \brief setScale shortcut.
	*
	* Gets the transform and calls the setScale member function.
	*
	* \param _scale the vec3 to update the scale with.
	* \see myengine::Transform
	*/
	void Component::setScale(vec3 _scale)
	{
		getTransform()->setScale(_scale);
	}

	/**
	* \brief setRotation shortcut.
	*
	* Gets the transform and calls the setRotation member function.
	*
	* \param _rotation the vec3 to update the rotation with.
	* \see myengine::Transform
	*/
	void Component::setRotation(vec3 _rotation)
	{
		getTransform()->setRotation(_rotation);
	}

	/**
	* \brief Shortcut for getCamera.
	* 
	* Goes through core and returns the camera by name. 
	* 
	* \return myengine::Camera
	*/
	std::shared_ptr<Camera> Component::getCamera()
	{
		return getCore()->getEntityByName("Camera")->getComponent<Camera>();
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

	/**
	* \brief Shortcut for getPosition. 
	* 
	* Gets the transform and then gets the position.
	* 
	* \return m_position the position of the object.
	*/
	vec3 Component::getPosition()
	{
		return getTransform()->getPosition();
	}

	/**
	* \brief Check for Intersect
	* 
	* Used to check for when the mouse is hovering over a GUI component and returns True or False.
	*/
	bool Component::intersect(vec2 _mouse, vec4 _rectangle)
	{
		if (_mouse.x < _rectangle.x)
		{
			return false;
		}

		if (_mouse.x > _rectangle.x + _rectangle.z)
		{
			return false;
		}

		if (_mouse.y < _rectangle.y)
		{
			return false;
		}

		// W is for vec4 height
		if (_mouse.y > _rectangle.y + _rectangle.w)
		{
			return false;
		}

		return true;
	}
}