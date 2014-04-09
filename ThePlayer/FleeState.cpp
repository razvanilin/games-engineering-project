/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "FleeState.h"

void FleeState::execute(Enemy* owner, float frameTime)
{
	// Get output frm steering behaviour
	SteeringOutput steering = _flee.getSteering();
	// We are going to use angular velocity. -X-rotation = z movement
	// Z-rotation = X movement
	btVector3 linear = btVector3(steering.direction.X, steering.direction.Y, -steering.direction.Z);
	linear.setY(0.0f);
	owner->getRigidBody()->activate(true);
	owner->getRigidBody()->setLinearVelocity(linear);
}