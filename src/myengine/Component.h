#include <memory>

namespace myengine
{
	struct Entity;

	struct Component
	{
	private:
		std::weak_ptr<Entity> entity;
	};
}