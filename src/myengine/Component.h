#pragma once

#include <memory>

namespace myengine
{
	struct Core;
	struct Entity;

	struct Component
	{
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();
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