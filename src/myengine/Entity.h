#include <memory>
#include <vector>
#include <iostream>

namespace myengine
{
	struct Core;
	struct Component;
	struct Transform;

	struct Entity
	{
		/**
		* \brief Adds a component.
		* 
		* Template function for adding a component to the entity.
		* Sets the entity of the component as itself, adds the component to a relative list,
		* then initialises the component.
		* 
		* \warning Component must be a part of the engine for it to work. 
		* Adding a custom one will show an error.
		*/ 
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			rtn->entity = self;	// Sets the component entity as this
			components.push_back(rtn);
			rtn->onInitialize();	// Initialises the component
			return rtn;
		}
		
		/**
		* \brief Gets a component.
		* 
		* Template function for getting a component from the entity. 
		* Iterates through the components list to find the requested component. 
		* 
		* \attention Function will exit early if it doesn't find the component. 
		* \return std::shared_ptr<T> rtn
		*/
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t ci = 0; ci < components.size(); ci++)
			{
				// Check if the component matches the one we are trying to find
				std::shared_ptr<T> rtn = std::dynamic_pointer_cast<T>(components.at(ci));

				// If the component matches, return it 
				if (rtn)
				{
					std::cout << "Component match!" << std::endl;
					return rtn;
				}
			}
			throw std::exception();	// Early exit
		}

		/**
		* Gets and returns the core of the engine.
		*
		* \return std::shared_ptr<Core> core
		*/
		std::shared_ptr<Core> getCore();

		/**
		* Gets and returns the transform created when adding an entity.
		*
		* \return std::shared_ptr<Transform> transform.
		*/
		std::shared_ptr<Transform> getTransform();

		private:
			friend struct myengine::Core;
			std::vector<std::shared_ptr<Component>> components;
			std::weak_ptr<Entity> self;
			std::weak_ptr<Core> core;
			std::weak_ptr<Transform> transform;

			/**
			* \brief Updating the entity.
			* 
			* The tick function within Entity iterates through its components and 
			* calls the tick function to update themselves.
			* 
			* \param Passes through the deltatime calculated within the environment
			* and passed through the tick functions. 
			*/
			void tick(float _deltaTime);
			void display();
	};
}
