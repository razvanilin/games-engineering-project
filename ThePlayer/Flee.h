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

namespace GameEngine {
	class Flee
	{
	private:
		Entity* _character;
		Entity* _target;
		float _maxSpeed;
	public:
		Flee(Entity* character, Entity* target, float maxSpeed)
			: _character(character), _target(target), _maxSpeed(maxSpeed)
		{
		}
		~Flee() { }
		SteeringOutput getSteering();
	};
}