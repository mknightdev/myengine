#include "Resource.h"

namespace myengine
{
	struct AudioClip;
	struct SoundSource;

	struct Sound : Resource
	{
		void onInitialize();

	private:
		friend struct myengine::SoundSource;
		std::shared_ptr<AudioClip> audioClip; 
	};
}