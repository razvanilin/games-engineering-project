/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "Entity.h"
#include "SteeringBehaviour.h"

namespace GameEngine
{
	class Seek : public SteeringBehaviour
	{
	private:
		// The Entity being controlled by the Steering Behaviour
		Entity* _character;
		// The target for the Steering Behaviour
		Entity* _target;
		// Maximum speet of the Entity
		float _maxSpeed;
	public:
		// Creates a new Seek behaviour
		Seek(Entity* character, Entity* target, float maxSpeed)
			: _character(character), _target(target), _maxSpeed(maxSpeed)
		{
		}
		// Destroys a Seek behaviour
		~Seek() { }
		// Gets the output from calculating the steering behaviour
		SteeringOutput getSteering();
	};
}