#pragma once

#include <memory>
#include <SDL2/SDL.h>
#include "mymath.h"

namespace myengine
{
	struct Core;
	struct Entity;
	struct Keyboard;
	struct Transform;
	struct Mouse;
	struct Camera;
	struct Coin;

	struct Component
	{
		std::shared_ptr<Core> getCore();
		std::shared_ptr<Entity> getEntity();
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
		std::shared_ptr<Transform> getTransform();
		std::shared_ptr<Camera> getCamera();
		vec3 getPosition();
		bool getKeyDown(int _keyCode);

		float deltaTime();
		virtual void onInitialize();
		virtual void onDisplay();
		virtual void onTick(float _deltaTime);
		virtual void onTrigger();

		bool intersect(vec2 _mouse, vec4 _rectangle);

		void setPosition(vec3 _position);
		void setScale(vec3 _scale);
		void setRotation(vec3 _rotation);

	private:
		friend struct myengine::Entity;

		/**
		* Used for storing the core and navigating up the hierarchy.
		*/
		std::weak_ptr<Core> core;

		/**
		* Used for storing the entity it is attached to and navigating
		* up the hierarchy.
		*/
		std::weak_ptr<Entity> entity;


		/**
		* Used for updating the display of the component.
		*/
		void display();

		/**
		* Used for updating the position of the component.
		*/
		void tick(float _deltaTime);

		void trigger();

		void destroy();
	};
}
