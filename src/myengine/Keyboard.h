#include <vector>
#include <memory>

namespace myengine
{
	struct Core;

	struct Keyboard
	{
		static std::shared_ptr<Keyboard> create(std::weak_ptr<Core> _core);

		//bool getKey(int _keyCode);
		bool getKeyDown(int _keyCode);
		//bool getKeyUp(int _keyCode);

		void removeKey(int _keyCode);

		private:
			friend struct myengine::Core;

			/**
			* Stores the keyCodes pressed in the SDL poll event.
			*/
			std::vector<int> keyCodes;

			/**
			* Stores itself and is used to grant other classes access to the key states.
			*/
			std::weak_ptr<Keyboard> self;

			/**
			* Used for storing the core and navigating up the hierarchy.
			*/ 
			std::weak_ptr<Core> core;
	};
}