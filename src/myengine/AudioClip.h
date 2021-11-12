#include <AL/al.h>
#include <AL/alc.h>
#include <iostream>
#include <vector>

namespace myengine
{
	struct AudioClip
	{
		AudioClip(std::string _fileName);
		void loadOgg(const std::string& _fileName, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq);
		ALuint GetId();

		std::string ErrorCheck(ALCenum _error);

	private:
		ALuint id;
	};
}