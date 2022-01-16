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
		
		/// Stores the audio clip.
		std::shared_ptr<AudioClip> audioClip; 
	};
}