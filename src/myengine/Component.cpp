#include "Component.h"
#include "Entity.h"
#include "Core.h"

namespace myengine
{
	void Component::tick()
	{
		onTick();
	}

	void Component::onTick()
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

	std::shared_ptr<Transform> Component::getTransform()
	{
		return getEntity()->getTransform();
	}
}