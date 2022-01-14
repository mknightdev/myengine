#pragma once

#include <SDL2/SDL.h>
#include <AL/alc.h>

#include <memory>
#include <vector>

#include "Exception.h"

namespace myengine
{
	struct Entity;
	struct Environment;
	struct Keyboard;
	struct Mouse;
	struct ResourceManager;
	struct Camera;
	struct SphereCollider;

	/**
	* \brief This is the brief description. 
	* 
	* This is the detailed description.
	* 
	* \param _this This is a parameter.
	*/
	struct Core
	{
		static std::shared_ptr<Core> initialize();

		void start();
		void stop();

		// Add clear function
		// Add get entities function
		void clear();

		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Entity> addEntity(const std::string _name);
		std::shared_ptr<Keyboard> getKeyboard();
		std::shared_ptr<Mouse> getMouse();
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<ResourceManager> getResourceManager();

		/**
		* \brief Gets the Entity
		* 
		* Checks if the entity exists, then returns the requested one.
		* \attention Function will exit early if it doesn't find the component. 
		* \return std::shared_ptr<T> rtn the entity to return.
		*/
		template<typename T>
		std::shared_ptr<T> getEntity()
		{
			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				// Check if the entity matches the one we are trying to find
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(entities.at(ei));

				// If we found the entity, return it
				if (rtn)
				{
					// Debugging
					std::cout << "Entity Found!" << std::endl;
					return rtn;
				}
			}

			throw Exception("Unable to get Entity");
		}

		std::shared_ptr<Entity> getEntityByName(const std::string _name);

		void registerCollider(std::shared_ptr<SphereCollider> _collider);
		void unregisterCollider(std::shared_ptr<SphereCollider> _collider);

		private:

			void setupEngine();
			void setupWindow();
			void setupGraphics();
			void setupAudio();

			/**
			* Can start or stop the engine depending on it's state. It gets set to true within the start() function,
			* and set to false within the stop() function.
			*/
			bool running;

			/**
			* \brief Stores entities.
			* 
			* Each entity that is created gets stored within entities.
			*/
			std::vector<std::shared_ptr<Entity>> entities;

			/**
			* \brief Stores all the colliders.
			* 
			* Contains all of the colliders that have been registered in the engine
			* and is used to detect collisions.
			* \see myengine::SphereCollider
			*/
			std::vector<std::shared_ptr<SphereCollider>> colliders;

			/**
			* Used for storing and updating deltaTime and retreiving delta time.
			*/
			std::shared_ptr<Environment> environment;

			/**
			* Used for storing and determing if a key has been pressed and released.
			*/
			std::shared_ptr<Keyboard> keyboard;

			/**
			* Used for storing and getting the user's mouse position.
			*/
			std::shared_ptr<Mouse> mouse;

			/**
			* Used for storing and loading resources within the engine.
			*/
			std::shared_ptr<ResourceManager> resourceManager;

			/**
			* Used for storing itself, and granting other classes to retrieve other 
			* components of the engine. 
			*/
			std::weak_ptr<Core> self;

			/**
			* The window created for SDL.
			*/
			SDL_Window* window;

			/**
			* The user's output device.
			*/
			ALCdevice* device;

			/**
			* The OpenAL soft context to link the device with.
			*/
			ALCcontext* context;
	};
}