#include "Component.h"
#include "AudioClip.h"

namespace myengine
{
	struct SoundSource : Component
	{
		void onInitialize();

		void PlaySound();

	private:
		ALuint srcID;
		std::shared_ptr<AudioClip> audioClip;
	};
}