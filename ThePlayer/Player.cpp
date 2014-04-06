#include "Player.h"
#include "EntityManager.h"
#include "HudManager.h"
#include "Game.h"
#include "EntityManager.h"
#include "Object.h"
#include "Collectable.h"
#include "MessageHandler.h"
#include "PhysicsEntity.h"
#include "Door.h"
#include <unordered_map>
#include <iostream>
#include "Room.h"

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

void Player::initialise(){
	_noiseAllowance = 100.0f;
}

void Player::loadContent(){
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(2.0f);
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	//_node->setPosition(vector3df(-13.0f, 0.0f, 33.0f));
	_node->setMaterialFlag(EMF_LIGHTING, false);
	std::string path = "textures/checked.jpg";
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(path.c_str()));
	_node->setVisible(false);
	this->setAlive(true);
	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(2.7f, 2.7f, 2.7f), 100.0f);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Player");
	physicsEntity->setRigidBody(_rigidBody);
	std::list<Entity*>* allColls = EntityManager::getNamedEntities("Collectable");
	auto iter = allColls->begin();
	while (iter != allColls->end()){
		Collectable* temp = (Collectable*)(*iter);
		_collectedItems[temp->getItemName()] = false;
		iter++;
	}
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

	if (inputHandler.isKeyDown(KEY_LSHIFT))
		_mod *= 2.0f;

	//make noise unless crouched, more when sprinting
	if (inputHandler.isKeyDown(KEY_LSHIFT) && (inputHandler.isKeyDown(KEY_KEY_W) || inputHandler.isKeyDown(KEY_KEY_A) || inputHandler.isKeyDown(KEY_KEY_S) || inputHandler.isKeyDown(KEY_KEY_D))){
		_noiseAllowance -= 0.020f;
	}
	else if (!inputHandler.isKeyDown(KEY_LCONTROL) && (inputHandler.isKeyDown(KEY_KEY_W) || inputHandler.isKeyDown(KEY_KEY_A) || inputHandler.isKeyDown(KEY_KEY_S) || inputHandler.isKeyDown(KEY_KEY_D))){
		_noiseAllowance -= 0.005f;
	}


	/* SETTING UP THE DIRECTION MATRIX */

	// preparing the matrix
	matrix4 mat0;
	mat0.setRotationAxisRadians(_yaw, vector3df(0, 1, 0));

	matrix4 mat1;
	mat1.setRotationAxisRadians(_pitch, vector3df(1, 0, 0));

	matrix4 mat = IdentityMatrix;
	mat = mat0 * mat1;

	// transform direction vectors based on the orientation of the player
	vector3df backward(.0f, .0f, -1.0f);
	vector3df toLeft(-1.0f, .0f, .0f);
	vector3df toRight(1.0f, .0f, .0f);
	vector3df forward(.0f, .0f, 1.0f);
	vector3df up(.0f, 1.0f, .0f);

	mat.transformVect(forward);
	mat.transformVect(backward);
	mat.transformVect(toLeft);
	mat.transformVect(toRight);

	setForward(forward);
	setUp(up);

	/* MOVEMENT */

	// setting key press events
	if (inputHandler.isKeyDown(KEY_KEY_D) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(toRight.X, 0.0f, -toRight.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_A) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(toLeft.X, 0.0f, -toLeft.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_S) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X, 0.0f, backward.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_W) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X, 0.0f, forward.Z)*_mod);
	}
	// setting double key press events
	if (inputHandler.isKeyDown(KEY_KEY_W) && inputHandler.isKeyDown(KEY_KEY_A) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X + toLeft.X, 0.0f, forward.Z - toLeft.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_W) && inputHandler.isKeyDown(KEY_KEY_D) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-forward.X + toRight.X, 0.0f, forward.Z - toRight.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_S) && inputHandler.isKeyDown(KEY_KEY_A) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X + toLeft.X, 0.0f, backward.Z - toLeft.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_KEY_S) && inputHandler.isKeyDown(KEY_KEY_D) && isDown()) {
		this->getRigidBody()->setLinearVelocity(btVector3(-backward.X + toRight.X, 0.0f, backward.Z - toRight.Z)*_mod);
	}

	// jump!
	if (inputHandler.isKeyDown(KEY_SPACE) && !inputHandler.wasKeyDown(KEY_SPACE) && isDown() && !isStealthActive()) {
		getRigidBody()->setLinearVelocity(btVector3(up.X, up.Y*_mod, up.Z));
		game.getAudioEngine()->play2D("sounds/common/jump.wav");
		_noiseAllowance -= 2.0f;
	}
	// TODO: fix the jumping and moving forward feature
	if (inputHandler.isKeyDown(KEY_SPACE) && inputHandler.isKeyDown(KEY_KEY_W) && isDown() && !isStealthActive()) {
		getRigidBody()->setLinearVelocity(btVector3(up.X - forward.X, up.Y, up.Z + forward.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_SPACE) && inputHandler.isKeyDown(KEY_KEY_S) && isDown() && !isStealthActive()) {
		getRigidBody()->setLinearVelocity(btVector3(up.X - backward.X, up.Y, up.Z + backward.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_SPACE) && inputHandler.isKeyDown(KEY_KEY_A) && isDown() && !isStealthActive()) {
		getRigidBody()->setLinearVelocity(btVector3(up.X + toLeft.X, up.Y, up.Z - toLeft.Z)*_mod);
	}
	if (inputHandler.isKeyDown(KEY_SPACE) && inputHandler.isKeyDown(KEY_KEY_D) && isDown() && !isStealthActive()) {
		getRigidBody()->setLinearVelocity(btVector3(up.X + toRight.X, up.Y, up.Z - toRight.Z)*_mod);
	}

	/* THROWABLE OBJECTS*/

	//action key
	if (inputHandler.isKeyDown(KEY_KEY_E) && !inputHandler.wasKeyDown(KEY_KEY_E)){
		if (_isCarrying){//dropping
			if (this->getCarriedItem() != NULL){
				this->_isCarrying = false;
				_hasKey = false;
				Message m(this->getCarriedItem(), "dropped", 0);
				MessageHandler::sendMessage(m);
				this->clearCarriedItem();
				_noiseAllowance -= 1.0f;
			}
		}
		else{//picking up
			std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
			vector3df playerPos = _node->getPosition();
			auto iter = objects->begin();
			while (iter != objects->end()){
				Object* obj = (Object*)(*iter);
				btVector3 hm = obj->getRigidBody()->getCenterOfMassPosition();
				vector3df objPos = vector3df(hm.getX(), hm.getY(), hm.getZ());
				vector3df toPlayer = playerPos - objPos;
				if (toPlayer.getLength() < 5){
					if (obj->getItemName() == "key") {
						_hasKey = true;
					}
					obj->setPickedUp(true);
					this->setCarriedItem(obj);
					this->_isCarrying = true;
					//does the player need a hint?
					HudManager* hud = (HudManager*)EntityManager::getNamedEntities("Hudman")->front();
					if (!hud->hasHintBeenShownFor("Throw")){
						hud->drawHintFor("Throw");
					}
					break;
				}
				iter++;
			}

		}
	}

	if (inputHandler.getCurrentMouse().LeftButton){
		if (_isCarrying){//dropping
			if (this->getCarriedItem() != NULL){
				this->_isCarrying = false;
				_hasKey = false;
				Message m(this->getCarriedItem(), "thrown", 0);
				MessageHandler::sendMessage(m);
				this->clearCarriedItem();
				_noiseAllowance -= 5.0f;
				//does the player need a hint?
				HudManager* hud = (HudManager*)EntityManager::getNamedEntities("Hudman")->front();
				if (!hud->hasHintBeenShownFor("Noise")){
					hud->drawHintFor("Noise");
				}
			}
		}
	}

	/* CHECKING THE DOORS */
	std::list<Entity*>* doors = EntityManager::getNamedEntities("Door");
	vector3df playerPos = _node->getPosition();
	auto doorIter = doors->begin();
	while (doorIter != doors->end()){

		Door* door = (Door*)(*doorIter);
		btVector3 btPos = door->getRigidBody()->getCenterOfMassPosition();
		vector3df doorPos = vector3df(btPos.x(), btPos.y(), btPos.z());
		vector3df toPlayer = playerPos - doorPos;

		if (toPlayer.getLength() < 3 && inputHandler.isKeyDown(KEY_KEY_F) && !inputHandler.wasKeyDown(KEY_KEY_F)) {
			btTransform transform = getRigidBody()->getCenterOfMassTransform();

			if (door->getDirection() == 1 && playerPos.X < doorPos.X && !door->isExit()) {
				transform.setOrigin(btVector3(doorPos.X + 2.0f, playerPos.Y, doorPos.Z));
			}
			else if (door->getDirection() == 2 && playerPos.X > doorPos.X && !door->isExit()) {
				transform.setOrigin(btVector3(doorPos.X - 2.0f, playerPos.Y, doorPos.Z));
			}
			else if (door->getDirection() == 3 && playerPos.Z < doorPos.Z && !door->isExit()) {
				transform.setOrigin(btVector3(doorPos.X, playerPos.Y, doorPos.Z + 2.0f));
			}
			else if (door->getDirection() == 4 && playerPos.Z > doorPos.Z && !door->isExit()) {
				transform.setOrigin(btVector3(doorPos.X, playerPos.Y, doorPos.Z - 2.0f));
			}
			else if (door->isExit() && _hasKey) {
				transform.setOrigin(btVector3(doorPos.X - 2.0f, playerPos.Y, doorPos.Z));
			}
			getRigidBody()->setCenterOfMassTransform(transform);
		}
		doorIter++;
	}
	/* GET THE ROOM THE PLAYER IS IN */
	std::list<Entity*>* rooms = EntityManager::getNamedEntities("Room");
	playerPos = _node->getPosition();
	auto iterator = rooms->begin();
	while (iterator != rooms->end()){

		Room* room = (Room*)(*iterator);
		vector3df roomPos = room->getPosition();
		vector3df roomScale = room->getScale();
		vector3df toPlayer = playerPos - roomPos;
		if (toPlayer.getLength() < roomScale.Z / 2)
			setCurrentRoom(room->getName());
		iterator++;
	}
}

void Player::rotate(float deltaYaw, float deltaPitch){
	_yaw -= deltaYaw;
	_pitch += deltaPitch;
	if (_pitch <= -1)
		_pitch = -1;
	if (_pitch >= 1)
		_pitch = 1;
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
void Player::handleMessage(const Message& message){
	if (message.message == "pickup"){

		Collectable* item = (Collectable*)message.data;
		if (!_collectedItems[item->getItemName()]){
			game.getAudioEngine()->play2D("sounds/common/pickup.wav", false);
			_collectedItems[item->getItemName()] = true;
		}

	}
	if (message.message == "Die"){
		this->setAlive(false);
	}
}