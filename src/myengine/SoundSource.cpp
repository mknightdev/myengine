#include "SoundSource.h"

namespace myengine
{
	/**
	* \brief Intialises the SoundSource. 
	* 
	* Loads in the sound file and generates the sources to play it with srcID. 
	* 
	* \warning Can throw an exception if it fails to generate the sources.
	* It will print to the console if it does. 
	*/ 
	void SoundSource::onInitialize()
	{
		ALCenum error;

		audioClip = std::make_shared<AudioClip>("../resources/sounds/doorbell");

		srcID = 0;
		alGenSources(1, &srcID);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in GenSources:" << audioClip->ExceptionCheck(error) << std::endl;
		}
	}

	/**
	* \brief Plays the loaded sound.
	* 
	* Adds a listener into the scene (the ears of the player) and plays the sound
	* stored in AudioClip by getting its ID.
	* 
	* \warning Can throw an exception if it fails to add the listener, source, or by playing it.
	*/
	void SoundSource::PlaySound()
	{
		ALCenum error;

		alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Listener3f:" << audioClip->ExceptionCheck(error) << std::endl;
		}

		alSource3f(srcID, AL_POSITION, 0.0f, 0.0f, 0.0f);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Source3f: " << audioClip->ExceptionCheck(error) << std::endl;
		}

		alSourcei(srcID, AL_BUFFER, audioClip->GetId());
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in Sourcei: " << audioClip->ExceptionCheck(error) << std::endl;
		}

		//alSourcef(sid, AL_PITCH, variance);
		//alSourcef(srcID, AL_GAIN, 100);
		alSourcePlay(srcID);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in SourcePlay: " << audioClip->ExceptionCheck(error) << std::endl;
		}
	}
}