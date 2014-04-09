/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Seek.h"

using namespace irr::core;

namespace GameEngine {
	SteeringOutput Seek::getSteering()
	{
		// Create output
		SteeringOutput steering;

		// Calculate direction. This is the vector from the character to the target
		vector3df characterPos = _character->getNode()->getPosition();
		vector3df targetPos = _target->getNode()->getPosition();
		vector3df direction = targetPos - characterPos;

		// We want to travel in this direciton at max speed
		// Normalise the direction vector (make 1 unit long) and multiply by max speed
		direction = direction.normalize();
		direction *= _maxSpeed;

		// Use this in the steering output. Rotation is 0
		steering.direction = direction;
		steering.rotation = 0.0f;

		// Return steering direction
		return steering;
	}
}