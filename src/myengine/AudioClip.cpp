#include "AudioClip.h"

#define STB_VORBIS_IMPLEMENTATION
#include <stb_vorbis.c>

namespace myengine
{
	AudioClip::AudioClip(std::string _fileName)
	{
		format = 0;
		freq = 0;
		id = 8;

		alGenBuffers(1, &id);

		loadOgg(_fileName + ".ogg", bufferData, format, freq);

		alBufferData(id, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
	}

	void AudioClip::loadOgg(const std::string& _fileName, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq)
	{
		int channels = 0;
		int sampleRate = 0;
		short* output = NULL;	// Always 2 chars

		size_t samples = stb_vorbis_decode_filename(_fileName.c_str(), &channels, &sampleRate, &output);

		if (samples == -1) { throw std::exception(); }

		std::cout << "Sound loaded: " << _fileName.c_str() << std::endl;

		// Record the format required by OpenAL
		if (channels == 1)
		{
			format = AL_FORMAT_MONO16;
		}
		else
		{
			format = AL_FORMAT_STEREO16;
		}

		// Record the sample rate required by OpenAL
		freq = sampleRate;

		_buffer.resize(samples * 2);
		memcpy(&_buffer.at(0), output, _buffer.size());

		// Clean up the read data
		free(output);
	}

	ALuint AudioClip::GetId()
	{
		return id;
	}
}