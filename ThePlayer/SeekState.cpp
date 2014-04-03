#include "SeekState.h"

void SeekState::execute(Enemy* owner, float frameTime)
{
	// Get output frm steering behaviour
	SteeringOutput steering = _seek.getSteering();
	// We are going to use angular velocity. -X-rotation = z movement
	// Z-rotation = X movement
	btVector3 linear = btVector3(steering.direction.X, steering.direction.Y, steering.direction.Z);
	linear.setY(0.0f);
	owner->getRigidBody()->activate(true);
	owner->getRigidBody()->setLinearVelocity(linear);
}