/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "StateNormal.h"

using namespace GameEngine;

void StateNormal::execute(Enemy* owner, float deltaTime){
	//set the angular velocity of the enemy to 0
	owner->getRigidBody()->setLinearVelocity(btVector3(0,0,0));
}