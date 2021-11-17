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
		std::weak_ptr<Mouse> self;
		std::weak_ptr<Core> core;
		vec2 mousePosition;
		bool canUpdate;
	};
}