#include "AudioClip.h"

#define STB_VORBIS_IMPLEMENTATION
#include <stb_vorbis.c>

namespace myengine
{
	void AudioClip::onInitialize()
	{
		std::cout << "test" << std::endl;
	}

	/**
	* \brief Initialises the AudioClip. 
	* 
	* Initialises the audio by generating buffers, loads the file and fills a buffer with audio data.
	* 
	* \param _fileName Takes in a string for the audio file name. 
	* \attention Audio extension must be .ogg
	* \warning Will throw an exception if it fails to generate the buffers, or fails to fill the buffer data.
	*/
	AudioClip::AudioClip(std::string _fileName)
	{
		ALenum format = 0;
		ALint freq = 0;
		std::vector<char> bufferData;

		id = 0;

		ALCenum error;

		alGenBuffers(1, &id);	// If it doesn't start at 1, it likely didn't setup the device.
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Exception in GenBuffers: " << ExceptionCheck(error) << std::endl;
		}

		loadOgg(_fileName + ".ogg", bufferData, format, freq);

		alBufferData(id, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Exception in BufferData: " << ExceptionCheck(error) << std::endl;
		}
	}

	/**
	* \brief Loads an .ogg audio file. 
	* 
	* Decodes the .ogg audio file and generates the samples, channels, sample rate and output needed.
	* 
	* \param _fileName The string to load that was passed in through the AudioClip constructor.
	* \param _buffer The vector reference to be resized and memory to copy into it from loading the samples.
	* \param _format The audio format to play in; Mono or Stereo.
	* \param _freq The sample rate generated from decoding the audio file. 
	*/
	void AudioClip::loadOgg(const std::string& _fileName, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;

		// !! Samples must be a multiple of 4 if AL_FORMAT_STEREO16 !!
		size_t samples = stb_vorbis_decode_filename(_fileName.c_str(), &channels, &sampleRate, &output);
		samples = samples - samples % 4;

		if (samples == -1) { throw std::exception(); }

		std::cout << "Sound loaded: " << _fileName.c_str() << std::endl;

		// Record the format required by OpenAL
		if (channels == 1)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_STEREO16;
		}

		// Record the sample rate required by OpenAL
		_freq = sampleRate;

		_buffer.resize(samples * 2);
		memcpy(&_buffer.at(0), output, _buffer.size());

		// Clean up the read data
		free(output);
	}

	/**
	* \brief Returns the AudioClip's ID. 
	*
	* Used within SoundSource to retrieve the audio data that will be played.
	*/
	ALuint AudioClip::GetId()
	{
		return id;
	}

	/**
	* \brief OpenAL Soft exception checking.
	* 
	* \param _error Passes through the exception from SoundSource and decodes it.
	* \return A message detailing the exception when setting up, or playing the audio.  
	*/
	std::string AudioClip::ExceptionCheck(ALCenum _error)
	{
		if (_error == AL_INVALID_VALUE)
		{
			return " Invalid value";
		}
		else if (_error == AL_INVALID_ENUM)
		{
			return " Invalid enum";
		}
		else if (_error == AL_INVALID_OPERATION)
		{
			return " Invalid operation";
		}
		else if (_error == AL_OUT_OF_MEMORY)
		{
			return " Not enough memory";
		}
		else if (_error == AL_INVALID_NAME)
		{
			return " Invalid name";
		}

		return " Not sure";
	}
}