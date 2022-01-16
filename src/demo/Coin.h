#include <myengine/Component.h>

namespace myengine
{
	struct SoundSource;

	struct Coin : Component
	{
		void onInitialize();
		void onTick(float _deltaTime);
		void onTrigger();

	private:
		/// Boolean to prevent from multiple plays of the audio 
		bool hasPlayed;

		/**
		* \brief Stores the Audio.
		* 
		* Used when playing the audio source provided.
		* 
		* \see myengine::SoundSource
		*/
		std::shared_ptr<SoundSource> audio;
	};
}