#include "FleeState.h"

void FleeState::execute(Enemy* owner, float frameTime)
{
	// Get output frm steering behaviour
	SteeringOutput steering = _flee.getSteering();
	// We are going to use angular velocity. -X-rotation = z movement
	// Z-rotation = X movement
	btVector3 angular = btVector3(steering.direction.Z, 0.0f, -steering.direction.X);
	owner->getRigidBody()->activate(true);
	owner->getRigidBody()->setAngularVelocity(angular);
}