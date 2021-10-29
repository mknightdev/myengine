#include <vector>
#include <memory>

namespace myengine
{
	struct Core;

	struct Keyboard
	{
		static std::shared_ptr<Keyboard> create(std::weak_ptr<Core> _core);
		//std::shared_ptr<Core> Keyboard::getCore();

		bool getKey(int _keyCode);
		bool getKeyDown(int _keyCode);
		bool getKeyUp(int _keyCode);

		void removeKey(int _keyCode);

		private:
			friend struct myengine::Core;
			std::vector<int> keyCodes;
			std::weak_ptr<Keyboard> self;
			std::weak_ptr<Core> core;
	};
}