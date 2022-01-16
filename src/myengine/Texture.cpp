#include "Texture.h"
#include "Exception.h"

#include <iostream>

namespace myengine
{
	/**
	* \brief Initialises the Texture
	* 
	* Initialises the texture by getting the path and adding the .png extension.
	* 
	* \attention Can support .png and .jpg files, other formats not supported.
	* \warning Will throw an exception if no file with the tried extensions can be found.
	*/
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
			texture = std::make_shared<myrenderer::Texture>(GetPath() + ".jpeg", w, h);
		}

		if (!texture)
		{
			throw Exception("Failed to load '" + GetPath() + "'");
		}
	}
}