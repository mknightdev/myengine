#include "Texture.h"
#include "Exception.h"

#include <iostream>

namespace myengine
{
	void Texture::onInitialize()
	{
		int w = 0;
		int h = 0;

		texture = std::make_shared<myrenderer::Texture>(GetPath() + ".png", w, h);

		if (!texture)
		{
			texture = std::make_shared<myrenderer::Texture>(GetPath() + ".jpg", w, h);
		}

		if (!texture)
		{
			throw Exception("Failed to load '" + GetPath() + "'");
		}
	}
}