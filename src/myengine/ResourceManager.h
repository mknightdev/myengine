#include <memory>
#include <vector>
#include <string>

namespace myengine
{
	struct Core;
	struct Resource;

	struct ResourceManager
	{
		static std::shared_ptr<ResourceManager> create(std::weak_ptr<Core> _core);

		/**
		* \brief Loads a resource.
		* 
		* Loads a resource and checks if one is already cached. If it is, 
		* we return the cached one. If it is not, we create and store the new one and then return it.
		* 
		* \return The loaded resource.
		*/
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

		/** 
		* Stores itself and is used for granting access to other classes.
		*/
		std::weak_ptr<ResourceManager> self;
		
		/**
		* Stores the core and is used for navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* \brief Stores all resources.
		* 
		* Each time a new resource is loaded, it gets cached to here to be loaded from,
		* rather than creating a new one each time.
		*/
		std::vector<std::shared_ptr<Resource>> resources;
	};
}