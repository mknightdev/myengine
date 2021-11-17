#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include "Environment.h"

namespace myengine
{
	void Component::tick(float _deltaTime)
	{
		onTick(_deltaTime);
	}

	void Component::onTick(float _deltaTime)
	{

	}

	void Component::display()
	{
		onDisplay();
	}

	void Component::onDisplay()
	{

	}

	void Component::onInitialize()
	{

	}

	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore();
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock();	// Makes weakptr into a shared
	}

	std::shared_ptr<Keyboard> Component::getKeyboard()
	{
		return getCore()->getKeyboard();
	}

	std::shared_ptr<Mouse> Component::getMouse()
	{
		return getCore()->getMouse();
	}

	std::shared_ptr<Transform> Component::getTransform()
	{
		return getEntity()->getTransform();
	}

	float Component::deltaTime()
	{
		return getCore()->getEnvironment()->getDeltaTime();
	}
}