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
		virtual void onTick(float _deltaTime);
		virtual void onDisplay();
		virtual void onInitialize();

		private:
			friend struct myengine::Entity;
			std::weak_ptr<Core> core;
			std::weak_ptr<Entity> entity;
			void tick(float _deltaTime);
			void display();
	};
}
