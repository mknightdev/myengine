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
	* Loads in the sound file and generates the sources to play it with srcID. 
	* 
	* \warning Can throw an exception if it fails to generate the sources.
	* It will print to the console if it does. 
	*/ 
	void SoundSource::onInitialize()
	{
		ALCenum error;

		//audioClip = std::make_shared<AudioClip>("resources/sounds/doorbell2");

		srcID = 0;
		alGenSources(1, &srcID);
		CheckError();
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
		SetPosition(getPosition().x, getPosition().y, getPosition().z);
		//SetListener(getCamera()->getCameraPos().x, getCamera()->getCameraPos().y, getCamera()->getCameraPos().z);
	}

	/**
	* \brief Plays the loaded audio.
	*/
	void SoundSource::Play()
	{
		alSourcei(srcID, AL_BUFFER, audioClip->GetId());
		CheckError();

		alSourcePlay(srcID);
		CheckError();
	}

	/**
	* \brief Pauses the playing audio.
	*/
	void SoundSource::Pause()
	{
		alSourcePause(srcID);
		CheckError();
	}

	/**
	* \brief Stops the playing audio.
	*/
	void SoundSource::Stop()
	{
		alSourceStop(srcID);
		CheckError();
	}


	void SoundSource::setSound(std::shared_ptr<Sound> _sound)
	{
		audioClip = _sound->audioClip;
	}

	/**
	* \brief Sets the volume.
	* 
	* \param _volume is used to set the level of the audio.
	*/
	void SoundSource::SetVolume(ALfloat _volume)
	{
		alSourcef(srcID, AL_GAIN, _volume);
		CheckError();
	}

	/**
	* \brief Sets the pitch.
	* 
	* \param _pitch is used to set the pitch value of the audio. 
	*/
	void SoundSource::SetPitch(ALfloat _pitch)
	{
		alSourcef(srcID, AL_PITCH, _pitch);
		CheckError();
	}

	/**
	* \brief Sets the position.
	* 
	* \param _x sets the x position of the audio. 
	* \param _y sets the y position of the audio.
	* \param _z sets the z position of the audio.
	*/
	void SoundSource::SetPosition(ALfloat _x, ALfloat _y, ALfloat _z)
	{
		alSource3f(srcID, AL_POSITION, _x, _y, _z);
		CheckError();
	}

	/**
	* \brief Sets the looping.
	* 
	* \param _state is used to set if the audio should loop or not.
	*/
	void SoundSource::SetLooping(bool _state)
	{
		alSourcei(srcID, AL_LOOPING, _state);
		CheckError();
	}

	/**
	* \brief Sets the listener.
	* 
	* \param _x sets the x position of the listener.
	* \param _y sets the y position of the listener.
	* \param _z sets the z position of the listener. 
	*/
	void SoundSource::SetListener(ALfloat _x, ALfloat _y, ALfloat _z)
	{
		alListener3f(AL_POSITION, _x, _y, _z);
		CheckError();
	}

	/**
	* \brief Error checking for audio
	* 
	* Checks for any errors when making changes with audio, or changing the state.
	* 
	* \warning Will throw an exception if an error is detected. A message will be displayed to the console. 
	* \see Exception
	*/
	void SoundSource::CheckError()
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
		CheckError();
	}

	// TODO:
	// position, isPlaying, etc
	// press p to pause
}