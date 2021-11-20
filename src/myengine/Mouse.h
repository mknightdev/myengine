#include <memory>
#include "mymath.h"

namespace myengine
{
	struct Core;

	struct Mouse
	{
		static std::shared_ptr<Mouse> create(std::weak_ptr<Core> _core);
		vec2 getMousePosition();

	private:
		friend struct myengine::Core;

		/**
		* Stores itself and is used to grant access to other classes
		* to get access to the mouse's position.
		*/
		std::weak_ptr<Mouse> self;

		/**
		* Stores the core and is used for navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* Stores the position of the mouse.
		*/
		vec2 mousePosition;
	};
}