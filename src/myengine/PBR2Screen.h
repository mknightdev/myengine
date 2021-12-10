#pragma once

#include "Component.h"

#include <myrenderer/myrenderer.h>

namespace myengine
{
	struct Mesh;
	struct Texture;

	struct PBR2Screen : Component
	{
		/* TODO:
			(look at 3DGP for reference)

			Create intersect function

			Display GUI buttons to swap scenes:
				Call scene one function if button clicked
				Call scene two function if other button clicked

			Create back buttons on the other scenes to return to menu

		*/

		/*
			oninit
				adds relevant entities to display
					store them as a member variable
			onTick
				if a is pressed, go through all entities added and destroy them
				getcore->clear;
					All entities, including the screen
				Create new menu screen

				if back button is pressed, clear screen and engine
					Add new instance of menu screen
		*/

		void onInitialize();
		void onTick(float _deltaTime);

	private:
		friend struct myengine::Core;

		// store entities needed here
		std::shared_ptr<Entity> sphereOne;
		std::shared_ptr<Entity> sphereTwo;
		std::shared_ptr<Entity> sphereThree;
		std::shared_ptr<Entity> sphereFour;
	};
}