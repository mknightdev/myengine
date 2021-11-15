#include <string>
#include <memory>
#include <vector>

namespace myengine
{
	struct Core;

	struct Resource
	{
		virtual void onInitialize();	// Makes it a polymorphic class for dynamic casting

		template <typename T>
		std::shared_ptr<T> load(const std::string& _path)
		{
			// Creates an empty sharedptr of the Resource
			// E.g., Loading a AudioClip will create an empty AudioClip sharedptr
			std::shared_ptr<T> rtn;

			for (size_t ri = 0; ri < resources.size(); ri++)
			{
				std::shared_ptr<Resource> r = resources.at(ri);
				if (r->path != _path) continue;
				rtn = std::dynamic_pointer_cast<T>(r);
				if (rtn) return rtn;
			}

			// If we don't have the resource cached already, cache it
			rtn = std::make_shared<T>();
			rtn->path = _path;
			rtn->onInitialize();
			resources.push_back(rtn);	// Make sure it works before adding it to the list

			return rtn;
		}

	private:
		friend struct myengine::Core;
		std::string path;
		std::vector<std::shared_ptr<Resource>> resources;
	};
}