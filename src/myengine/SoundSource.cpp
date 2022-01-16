#include "SoundSource.h"
#include "Exception.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Entity.h"
#include "Camera.h"
#include "Sound.h"

namespace myengine
{
	/**
	* \brief Intialises the SoundSource. 
	* 
	* Initialises the loaded sound source and generates the sources to play it with srcID. 
	* 
	* \warning Can throw an exception if it fails to generate the sources.
	* It will print to the console if it does. 
	*/ 
	void SoundSource::onInitialize()
	{
		ALCenum error;

		srcID = 0;
		alGenSources(1, &srcID);
		checkError();
	}

	/**
	* \brief Updates the sound each frame.
	* 
	* onTick runs every frame and is used to update the data for the sound for 
	* positional audio.
	* 
	* \attention This version doesn't require deltaTime, because it doesn't need to multiply it with anything.
	*/
	void SoundSource::onTick(float _deltaTime)
	{
		setPosition(getPosition().x, getPosition().y, getPosition().z);
	}

	/**
	* \brief Plays the loaded audio.
	* 
	* Retrieves the source and plays it. 
	* 
	* \see myengine::AudioClip
	*/
	void SoundSource::play()
	{
		alSourcei(srcID, AL_BUFFER, audioClip->GetId());
		checkError();

		alSourcePlay(srcID);
		checkError();
	}

	/**
	* \brief Pauses the audio.
	* 
	* Pauses the audio using the id of it.
	*/
	void SoundSource::pause()
	{
		alSourcePause(srcID);
		checkError();
	}

	/**
	* \brief Stops the audio.
	* 
	* Stops the audio using the id of it.
	*/
	void SoundSource::stop()
	{
		alSourceStop(srcID);
		checkError();
	}

	/**
	* \brief Sets the Audio.
	* 
	* Loads in the audio using the resource manager and 
	* sets the audioClip as the loaded file. 
	* 
	* \see myengine::AudioClip
	* \see myengine::ResourceManager
	*/
	void SoundSource::setSound(std::shared_ptr<Sound> _sound)
	{
		audioClip = _sound->audioClip;
	}

	/**
	* \brief Sets the volume.
	* 
	* \param _volume is used to set the level of the audio.
	*/
	void SoundSource::setVolume(ALfloat _volume)
	{
		alSourcef(srcID, AL_GAIN, _volume);
		checkError();
	}

	/**
	* \brief Sets the pitch.
	* 
	* \param _pitch is used to set the pitch value of the audio. 
	*/
	void SoundSource::setPitch(ALfloat _pitch)
	{
		alSourcef(srcID, AL_PITCH, _pitch);
		checkError();
	}

	/**
	* \brief Sets the position.
	* 
	* \param _x sets the x position of the audio. 
	* \param _y sets the y position of the audio.
	* \param _z sets the z position of the audio.
	*/
	void SoundSource::setPosition(ALfloat _x, ALfloat _y, ALfloat _z)
	{
		alSource3f(srcID, AL_POSITION, _x, _y, _z);
		checkError();
	}

	/**
	* \brief Sets the looping.
	* 
	* \param _state is used to set if the audio should loop or not.
	*/
	void SoundSource::setLooping(bool _state)
	{
		alSourcei(srcID, AL_LOOPING, _state);
		checkError();
	}

	/**
	* \brief Sets the listener.
	* 
	* \param _x sets the x position of the listener.
	* \param _y sets the y position of the listener.
	* \param _z sets the z position of the listener. 
	*/
	void SoundSource::setListener(ALfloat _x, ALfloat _y, ALfloat _z)
	{
		alListener3f(AL_POSITION, _x, _y, _z);
		checkError();
	}

	/**
	* \brief Error checking for audio
	* 
	* Checks for any errors when making changes with audio, or changing the state.
	* 
	* \warning Will throw an exception if an error is detected. A message will be displayed to the console. 
	* \see Exception
	*/
	void SoundSource::checkError()
	{
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			throw Exception(audioClip->ExceptionCheck(error));
		}
	}

	/// Makes sure the sound stops playing once destroyed
	SoundSource::~SoundSource()
	{
		alSourceStop(srcID);
		checkError();
	}
}