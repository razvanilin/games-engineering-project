#include "StateSpin.h"

using namespace GameEngine;

void StateSpin::execute(Enemy* owner, float deltaTime){
	//activate rigidbody
	owner->getRigidBody()->activate(true);

	//set the angular velocity of the enemy to 0
	owner->getRigidBody()->setAngularVelocity(btVector3(0,10.0f,0));
}