#include "Sound.h"
#include "AudioClip.h"

namespace myengine
{
	/**
	* \brief Initialises the Sound
	* 
	* Initialises the sound by getting the path and adding the required .ogg extension. 
	* This gets passed through and loads the sound file. 
	*	
	* \attention Must be a .ogg file, no other format is supported. 	
	* \warning Will throw an exception if no file with the tried extension can be found.
	*/
	void Sound::onInitialize()
	{
		audioClip = std::make_shared<AudioClip>(GetPath() + ".ogg");
	}
}