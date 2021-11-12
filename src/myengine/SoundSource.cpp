#include "SoundSource.h"

namespace myengine
{
	void SoundSource::onInitialize()
	{
		audioClip = std::make_shared<AudioClip>("../resources/sounds/horn");

		srcID = 0;
		alGenSources(1, &srcID);
	}

	void SoundSource::onDisplay()
	{

	}

	void SoundSource::onTick(float _deltaTime)
	{

	}

	void SoundSource::PlaySound()
	{
		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSource3f(srcID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		alSourcei(srcID, AL_BUFFER, audioClip->GetId());
		//alSourcef(sid, AL_PITCH, variance);
		alSourcef(srcID, AL_GAIN, 100);
		alSourcePlay(srcID);
	}
}