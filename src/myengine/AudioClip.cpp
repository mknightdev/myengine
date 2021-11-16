#include "AudioClip.h"

#define STB_VORBIS_IMPLEMENTATION
#include <stb_vorbis.c>

namespace myengine
{
	void AudioClip::onInitialize()
	{
		std::cout << "test" << std::endl;
	}

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
			std::cout << "Error in GenBuffers: " << ErrorCheck(error) << std::endl;
		}

		loadOgg(_fileName + ".ogg", bufferData, format, freq);

		alBufferData(id, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
		error = alGetError();
		if (error != AL_NO_ERROR)
		{
			std::cout << "Error in BufferData: " << ErrorCheck(error) << std::endl;
		}
	}

	void AudioClip::loadOgg(const std::string& _fileName, std::vector<char> &_buffer, ALenum &_format, ALsizei &_freq)
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

	ALuint AudioClip::GetId()
	{
		return id;
	}

	std::string AudioClip::ErrorCheck(ALCenum _error)
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