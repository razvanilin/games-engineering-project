#include "Player.h"
#include "Game.h"
#include "EntityManager.h"
#include "Object.h"
#include "MessageHandler.h"
#include <unordered_map>
#include <iostream>

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

void Player::initialise(){

}

void Player::loadContent(){
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	_node->setMaterialFlag(EMF_LIGHTING, false);
	std::string path = "textures/checked.jpg";
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(path.c_str()));
	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(2.0f, 2.0f, 2.0f), 50.0f);
}

void Player::update(float deltaTime){

	getRigidBody()->activate();
	
	// modifying the speed based on the movement mode
	if (inputHandler.isKeyDown(KEY_LCONTROL))
		// stealth movement
		_mod = 2.0f;
	else
		// normal movement
		_mod = 5.0f;

	// setting the position of the node based on the rigid body
	btVector3 point = _rigidBody->getCenterOfMassPosition();
	_node->setPosition(vector3df(point.getX(), point.getY(), point.getZ()));
	btQuaternion quat = _rigidBody->getOrientation();
	quaternion q(quat.getX(), quat.getY(), quat.getZ(), quat.getW());
	vector3df eular;
	q.toEuler(eular);
	eular *= RADTODEG;
	_node->setRotation(eular);

	// preparing the matrix
	matrix4 mat0;
	mat0.setRotationAxisRadians(_yaw, vector3df(0, 1, 0));

	matrix4 mat1;
	mat1.setRotationAxisRadians(_pitch, vector3df(1, 0, 0));

	matrix4 mat = IdentityMatrix;
	mat = mat0 * mat1;

	// transform direction vectors based on the orientation of the player
	vector3df backward(.0f, .0f, -1.0f*_mod);
	vector3df toLeft(-1.0f*_mod, .0f, .0f);
	vector3df toRight(1.0f*_mod, .0f, .0f);
	vector3df forward(.0f, .0f, 1.0f*_mod);
	vector3df up(.0f, 1.0f, .0f);

	mat.transformVect(forward);
	mat.transformVect(backward);
	mat.transformVect(toLeft);
	mat.transformVect(toRight);

	setForward(forward);
	setUp(up);

	// setting key press events
	if (inputHandler.isKeyDown(KEY_KEY_D)) {
		this->getRigidBody()->setLinearVelocity(btVector3(toRight.X, 0.0f, -toRight.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_A)) {
		this->getRigidBody()->setLinearVelocity(btVector3(toLeft.X, 0.0f, -toLeft.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_S)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X, 0.0f, backward.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_W)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X, 0.0f, forward.Z));
	}
	// setting double key press events
	if (inputHandler.isKeyDown(KEY_KEY_W) && inputHandler.isKeyDown(KEY_KEY_A)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X + toLeft.X, 0.0f, forward.Z - toLeft.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_W) && inputHandler.isKeyDown(KEY_KEY_D)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X + toRight.X, 0.0f, forward.Z - toRight.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_S) && inputHandler.isKeyDown(KEY_KEY_A)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X + toLeft.X, 0.0f, backward.Z - toLeft.Z));
	}
	if (inputHandler.isKeyDown(KEY_KEY_S) && inputHandler.isKeyDown(KEY_KEY_D)) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X + toRight.X, 0.0f, backward.Z - toRight.Z));
	}

	// jump!
	if (inputHandler.isKeyDown(KEY_SPACE) && !inputHandler.wasKeyDown(KEY_SPACE)) {
		getRigidBody()->setLinearVelocity(btVector3(up.X, up.Y*_mod, up.Z));
	}
	// TODO: fix the jumping and moving forward feature
	if (inputHandler.isKeyDown(KEY_SPACE) && !inputHandler.wasKeyDown(KEY_SPACE) && inputHandler.isKeyDown(KEY_KEY_W)) {
		getRigidBody()->setLinearVelocity(btVector3(up.X - forward.X, (up.Y + forward.Y)*_mod, up.Z + forward.Z));
	}

	//action key
	if (inputHandler.isKeyDown(KEY_KEY_E) && !inputHandler.wasKeyDown(KEY_KEY_E)){
		if (_isCarrying){//dropping
			if (this->getCarriedItem() != NULL){
				cout << "item at location " << this->getCarriedItem() << " now dropped" << endl;			
				this->_isCarrying = false;
				cout << "isCarrying: " << _isCarrying << endl;
				Message m(this->getCarriedItem(), "dropped", 0);
				MessageHandler::sendMessage(m);
				this->clearCarriedItem();
			}
		}else{//picking up
			std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
			vector3df playerPos = _node->getPosition();
			auto iter = objects->begin();
			while (iter!=objects->end()){
				Object* obj = (Object*)(*iter);
				btVector3 hm = obj->getRigidBody()->getCenterOfMassPosition();
				vector3df objPos = vector3df(hm.getX(), hm.getY(), hm.getZ());
				vector3df toPlayer = playerPos - objPos;
				if (toPlayer.getLength() < 5){
					obj->setPickedUp(true);
					this->setCarriedItem(obj);
					this->_isCarrying = true;
					cout << "item at location "<<this->getCarriedItem()<< " now picked up" << endl;
					cout << "isCarrying: " << _isCarrying << endl;
					break;
				}
				iter++;
			}			
		}
	}

	if (inputHandler.getCurrentMouse().LeftButton){
		if (_isCarrying){//dropping
			if (this->getCarriedItem() != NULL){
				cout << "item at location " << this->getCarriedItem() << " now thrown" << endl;
				this->_isCarrying = false;
				cout << "isCarrying: " << _isCarrying << endl;
				Message m(this->getCarriedItem(), "thrown", 0);
				MessageHandler::sendMessage(m);
				this->clearCarriedItem();
			}
		}
	}
}


void Player::rotate(float deltaYaw, float deltaPitch){
	_yaw -= deltaYaw;
	_pitch += deltaPitch;

	// rotate the rigid body according to the position of the mouse
	btTransform trans = getRigidBody()->getCenterOfMassTransform();
	btQuaternion q = btQuaternion::getIdentity();
	
	btQuaternion quat0;
	quat0.setRotation(btVector3(0, -1, 0), _yaw);

	btQuaternion quat1;
	quat1.setRotation(btVector3(1, 0, 0), _pitch);

	trans.setRotation(quat0);


	this->getRigidBody()->setCenterOfMassTransform(trans);
}