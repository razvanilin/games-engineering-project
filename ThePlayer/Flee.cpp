#include "Flee.h"

using namespace irr::core;

namespace GameEngine
{
	SteeringOutput Flee::getSteering()
	{
		// This is just Seek in reverse(so get direction away from target)
		// Create output
		SteeringOutput steering;

		// Calculate direciton. This is the vector from the target to the character
		vector3df characterPos = _character->getNode()->getPosition();
		vector3df targetPos = _target->getNode()->getPosition();
		vector3df direction = characterPos - targetPos;

		// We want to travel in this direciton at max speed.
		// Normalise the direction vector ( make 1 unit long) and multiply by max speed
		direction = direction.normalize();
		direction *= _maxSpeed;

		// Use this in the steering output. Rotation is 0
		steering.direction = direction;
		steering.rotation = 0.0f;

		return steering;
	}
}