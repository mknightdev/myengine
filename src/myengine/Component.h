#pragma once

#include <memory>
#include <SDL2/SDL.h>

namespace myengine
{
	struct Core;
	struct Entity;
	struct Keyboard;
	struct Transform;
	struct Mouse;

	struct Component
	{
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
		std::shared_ptr<Transform> getTransform();
		float deltaTime();
		virtual void onInitialize();
		virtual void onDisplay();
		virtual void onTick(float _deltaTime);

	private:
		friend struct myengine::Entity;

		/**
		* Used for storing the core and navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* Used for storing the entity it is attached to and navigating
		* up the hierarchy.
		*/
		std::weak_ptr<Entity> entity;

		void display();
		void tick(float _deltaTime);
	};
}
