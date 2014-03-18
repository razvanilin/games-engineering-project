#include "PhysicsEntity.h"
#include <btBulletDynamicsCommon.h>
#include "InputHandler.h"
#include "Game.h"

using namespace irr::core;

void PhysicsEntity::update(float deltaTime){
	// we have to take the rigid body's position and rotation and apply
	//it to our node

	//get the position of the rigid body
	btVector3 point = _rigidBody->getCenterOfMassPosition();
	//use this to set the position of the node
	_node->setPosition(vector3df(point.getX(), point.getY(), point.getZ()));

	//get the rotation of the rigid body. Tghis is represented by a quaternion
	const btQuaternion& quat = _rigidBody->getOrientation();

	//convert from a bullet quternion to an irrlicht one
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());

	//convert the quaternion into Eular rotations (x,y,z)
	vector3df eular;
	q.toEuler(eular);

	//convert the Eular rotation from RAD to DEG
	eular *= RADTODEG;

	// set the rotation of the node
	_node->setRotation(eular);	

	if(inputHandler.isKeyDown(KEY_KEY_Q)&&!inputHandler.wasKeyDown(KEY_KEY_Q)){
		_rigidBody->activate();
		_rigidBody->applyCentralImpulse(btVector3(rand()%20-10, rand()%10, rand()%20-10));
	}
	if(inputHandler.isKeyDown(KEY_KEY_E)&&!inputHandler.wasKeyDown(KEY_KEY_E)){
		_rigidBody->activate();
		_rigidBody->applyCentralImpulse(btVector3(-rand()%20+10, -rand()%10, -rand()%20+10));
	}
}
void PhysicsEntity::handleMessage(const Message& message){
	//check for collision message
	if (message.message=="COLLISION"){
		//check if we have collided with a wall
		//Data part of message wil be another entity
		if(((Entity*)message.data)->getName() == "Wall"){
			_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("flame.jpg"));
		}
		else if(((Entity*)message.data)->getName() == "Floor"){
			//set texture to original
			_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("checked.jpg"));
		}
	}
}
