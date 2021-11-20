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

		/**
		* \brief The resource path. 
		* 
		* Used to store and compare it when loading another resource. 
		* 
		* \see Texture
		* \see AudioClip
		*/
		std::string path;
	};
}