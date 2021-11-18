#include <memory>

namespace myengine
{
	struct Core;

	struct Environment
	{
		static std::shared_ptr<Environment> create(std::weak_ptr<Core> _core);
		float getDeltaTime();

		private:
			friend struct myengine::Core;

			/**
			* Stores itself and is used to grant access to other classes.
			* to get the deltaTime.
			*/
			std::weak_ptr<Environment> self;

			/**
			* Used for storing the core and navigating up the hierarchy.
			*/
			std::weak_ptr<Core> core;

			/**
			* The final calculated deltaTime.
			*/
			float deltaTime;

			/**
			* \brief The last time we calculated deltaTime.
			* 
			* Sets last time to current time, which gets calculated each tick. 
			* It gets used when calculating the difference between lastTime and currentTime.
			*/
			float lastTime;

			/**
			* brief The current time at the beginning of the tick.
			*/
			float currentTime;

			/**
			* Used to calculate the deltaTime each tick. 
			*/
			void tick();
	};
}