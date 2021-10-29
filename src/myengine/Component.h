#pragma once

#include <memory>
#include <SDL2/SDL.h>

namespace myengine
{
	struct Core;
	struct Entity;
	struct Keyboard;

	struct Component
	{
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Keyboard> getKeyboard();
		virtual void onTick();
		virtual void onDisplay();
		virtual void onInitialize();

		private:
			friend struct myengine::Entity;
			std::weak_ptr<Core> core;
			std::weak_ptr<Entity> entity;
			void tick();
			void display();
	};
}
