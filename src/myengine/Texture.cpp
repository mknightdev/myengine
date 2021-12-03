#include "Texture.h"

namespace myengine
{
	void Texture::onInitialize()
	{
		int w, h = 0;
		texture = std::make_shared<myrenderer::Texture>(GetPath() + ".png", w, h);
		
		// Try for other extensions
	}
}