#include <string>
#include <memory>
#include <vector>

namespace myengine
{
	struct ResourceManager;

	struct Resource
	{
		virtual void onInitialise();

	private:
		friend struct myengine::ResourceManager;
		std::string path;
	};
}