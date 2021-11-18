#include "Component.h"
#include "AudioClip.h"

namespace myengine
{
	struct SoundSource : Component
	{
		void onInitialize();
		void PlaySound();

	private:
		
		/**
		* Used to play the clip loading from AudioClip.
		*/
		ALuint srcID;

		/**
		* \brief Grants ownership to AudioClip.
		* 
		* Used for loading the sound file.
		*/
		std::shared_ptr<AudioClip> audioClip;
	};
}