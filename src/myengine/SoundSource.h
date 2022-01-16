#include "Component.h"
#include "AudioClip.h"

namespace myengine
{
	struct Sound;

	struct SoundSource : Component
	{
		void onInitialize();
		void onTick(float _deltaTime);

		void play();
		void stop();
		void pause();

		void setSound(std::shared_ptr<Sound> _sound);
		void setVolume(ALfloat _volume);
		void setPitch(ALfloat _pitch);
		void setPosition(ALfloat _x, ALfloat _y, ALfloat _z);
		void setLooping(bool _state);
		void setListener(ALfloat _x, ALfloat _y, ALfloat _z);

		~SoundSource();

	private:
		
		void checkError();

		/**
		* Used to play the clip loading from AudioClip.
		*/
		ALuint srcID;

		/**
		* Used to retrieve errors.
		*/
		ALCenum error;

		/**
		* \brief Grants ownership to AudioClip.
		* 
		* Used for loading the sound file.
		*/
		std::shared_ptr<AudioClip> audioClip;
	};
}