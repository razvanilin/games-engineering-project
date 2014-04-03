#include "Object.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"
#include "FreeCamera.h"
#include "PhysicsEntity.h"
#include "Room.h"
#include <iostream>

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an pickupable object. Initialises Entity and SM
Object::Object(std::string name, vector3df startPos) : Entity(-1, 0, "Object"){
	_pickedUp = false;
	_itemName = name;
	_startPos = startPos;
}


void Object::initialise(){
	Entity* player = EntityManager::getNamedEntities("Player")->front();
}

//Load content for the Object
void Object::loadContent(){
	//make a sphere
	//IAnimatedMesh* mesh = game.getDevice()->getSceneManager()->getMesh("meshes/house/Couch.obj");
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	//_node->setScale(vector3df(0.5f, 0.5f, 0.5f));
	//_node->setMesh(mesh);
	//set position to (0,0,0)
	_node->setPosition(_startPos);
	//set material properties
	//_node->setVisible(0);
	_node->setMaterialFlag(EMF_LIGHTING, false);
	std::string pathToTexture = "textures/" + _itemName + ".jpg";
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(pathToTexture.c_str()));

	//_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/BRNLEAT2.jpg"));
	//create rigid body (sphere with rad of 1)

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(1.0f, 1.0f, 1.0f), 10);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Object");
	physicsEntity->setRigidBody(_rigidBody);
}

float objDistance = 2.0f;

//updates the Object
void Object::update(float deltaTime){
	// throw power
	_mod = 15.0f;

	std::list<Entity*>* objects = EntityManager::getNamedEntities("Player");
	Player* player = (Player*)*(objects->begin());
	setForward(player->getForward());
	setUp(player->getUp());

	/* GET THE ROOM THE OBJECT IS IN */
	std::list<Entity*>* rooms = EntityManager::getNamedEntities("Room");
	vector3df objectPos = _node->getPosition();
	auto iterator = rooms->begin();
	while (iterator != rooms->end()){

		Room* room = (Room*)(*iterator);
		vector3df roomPos = room->getPosition();
		vector3df roomScale = room->getScale();
		vector3df toPlayer = objectPos - roomPos;
		if (toPlayer.getLength() < roomScale.Z / 2)
			setCurrentRoom(room->getName());
		iterator++;
	}





	//if object is picked up - it's position is fixed to the player <- you made a typo, Dave!
	if (_pickedUp){
		btRigidBody* body = getRigidBody();
		Entity* player = EntityManager::getNamedEntities("Player")->front();
		vector3df playerPos = player->getNode()->getPosition();
		
		// position of the rigid body and the node when it's picked up
		_forward = vector3df(-_forward.X, _forward.Y, _forward.Z);
		
		btVector3 f = btVector3(_forward.X, _forward.Y, _forward.Z);
		btVector3 newPos = btVector3(playerPos.X, playerPos.Y+1.0f, playerPos.Z) + f*objDistance;
		//if (newPos.y() <! -3.5) {
			btTransform transform = this->getRigidBody()->getCenterOfMassTransform();
			transform.setOrigin(newPos);
			body->setCenterOfMassTransform(transform);
		//}
	}
}

void Object::handleMessage(const Message& message){
	if (message.message == "pickedup"){
		this->_pickedUp = true;
	}

	if (message.message == "thrown"){
		_rigidBody->activate();
		this->_pickedUp = false;
		_rigidBody->setLinearVelocity(btVector3((_forward.X)*_mod, (_forward.Y)*_mod, (_forward.Z)*_mod));
		game.getAudioEngine()->play2D("sounds/common/throw.wav");
		
	}
	if (message.message == "dropped"){
		_rigidBody->activate();
		this->_pickedUp = false;
		

	}

}
