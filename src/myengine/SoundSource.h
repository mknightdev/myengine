#include "Component.h"
#include "AudioClip.h"

namespace myengine
{
	struct SoundSource : Component
	{
		void onInitialize();
		void onTick();

		void Play();
		void Stop();
		void Pause();


		void SetVolume(ALfloat _volume);
		void SetPitch(ALfloat _pitch);
		void SetPosition(ALfloat _x, ALfloat _y, ALfloat _z);
		void SetLooping(bool _state);
		//void SetVelocity();
		void SetListener(ALfloat _x, ALfloat _y, ALfloat _z);

	private:
		
		void CheckError();

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