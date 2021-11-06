#include <memory>
#include <glm/glm.hpp>

namespace myengine
{
	struct Core;

	struct Mouse
	{
		static std::shared_ptr<Mouse> create(std::weak_ptr<Core> _core);
		glm::vec2 getMousePosition();

	private:
		friend struct myengine::Core;
		std::weak_ptr<Mouse> self;
		std::weak_ptr<Core> core;
		glm::vec2 mousePosition;
	};
}