#include "SoundSource.h"

namespace myengine
{
	void SoundSource::onInitialize()
	{
		ALCenum error;

		audioClip = std::make_shared<AudioClip>("../resources/sounds/doorbell");

		srcID = 0;
		alGenSources(1, &srcID);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in GenSources:" << audioClip->ErrorCheck(error) << std::endl;
		}
	}

	void SoundSource::onDisplay()
	{

	}

	void SoundSource::onTick(float _deltaTime)
	{

	}

	void SoundSource::PlaySound()
	{
		ALCenum error;

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Listener3f:" << audioClip->ErrorCheck(error) << std::endl;
		}

		alSource3f(srcID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Source3f: " << audioClip->ErrorCheck(error) << std::endl;
		}

		alSourcei(srcID, AL_BUFFER, audioClip->GetId());
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Sourcei: " << audioClip->ErrorCheck(error) << std::endl;
		}

		//alSourcef(sid, AL_PITCH, variance);
		//alSourcef(srcID, AL_GAIN, 100);
		alSourcePlay(srcID);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in SourcePlay: " << audioClip->ErrorCheck(error) << std::endl;
		}
	}
}