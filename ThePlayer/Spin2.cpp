#include "Spin2.h"

void Spin2::execute(Enemy* owner, float deltaTime)
{
	owner->getRigidBody()->setAngularVelocity(_angular);
	_angular *= -1.0f;
}