/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Object.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"
#include "FreeCamera.h"
#include "PhysicsEntity.h"
#include "Room.h"
#include "HudManager.h"
#include <iostream>
#include <sstream>

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an pickupable object. Initialises Entity and SM
Object::Object(std::string name, std::string meshName, vector3df startPos, std::string startRoom) : Entity(-1, 0, "Object"){
	_pickedUp = false;
	_itemName = name;
	_meshName = meshName;
	_startPos = startPos;
	_mass = 0;
	_currentRoom = startRoom;
	_firstPicked = true;
}


void Object::initialise(){
	Entity* player = EntityManager::getNamedEntities("Player")->front();
}

//Load content for the Object
void Object::loadContent(){
	//make a sphere
	std::wstringstream path;
	path << "meshes/" << _itemName.c_str() << "/" << _meshName.c_str();
	IAnimatedMesh* mesh = game.getDevice()->getSceneManager()->getMesh(path.str().c_str());
	if (!mesh){
		std::cout << "Could not load " << _itemName.c_str() << " mesh" << std::endl;
		return;
	}
	_node = game.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(mesh);
	_node->setScale(_scale);
	//_node->setMesh(mesh);
	//set position to (0,0,0)
	_node->setPosition(_startPos);
	//set material properties
	//_node->setVisible(0);
	_node->setMaterialFlag(EMF_LIGHTING, false);

	//_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/BRNLEAT2.jpg"));
	//create rigid body (sphere with rad of 1)

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(0.5f, 0.5f, 0.5f),_mass);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Object");
	physicsEntity->setRigidBody(_rigidBody);
}

float objDistance = 3.0f;
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

	//if object is picked up - it's position is fixed to the player
	if (_pickedUp){
		// replace the rigid body with one that has the mass 10
		if (_firstPicked) {
			//PhysicsEngine::removeRigidBody(_rigidBody);
			_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(1.0f, 1.0f, 1.0f), 10);
			PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Object");
			physicsEntity->setRigidBody(_rigidBody);
			_firstPicked = false;
		}

		btRigidBody* body = getRigidBody();
		Entity* player = EntityManager::getNamedEntities("Player")->front();
		vector3df playerPos = player->getNode()->getPosition();

		// position of the rigid body and the node when it's picked up
		_forward = vector3df(-_forward.X, _forward.Y, _forward.Z);

		btVector3 f = btVector3(_forward.X, _forward.Y, _forward.Z);
		btVector3 newPos = btVector3(playerPos.X, playerPos.Y + 1.0f, playerPos.Z) + f*objDistance;
		//if (newPos.y() <! -3.5) {
		btTransform transform = this->getRigidBody()->getCenterOfMassTransform();
		transform.setOrigin(newPos);
		body->setCenterOfMassTransform(transform);
		//}
	}
	//does the player need a hint?
	HudManager* hud = (HudManager*)EntityManager::getNamedEntities("Hudman")->front();
	if (!hud->hasHintBeenShownFor("Object")){
		vector3df playerPos = ((Entity*)player)->getNode()->getPosition();
		vector3df objectPos = _node->getPosition();
		vector3df d = playerPos - objectPos;
		auto dist = d.getLength();
		if (d.getLength()<5){
			hud->drawHintFor("Object");
		}
	}
}

void Object::handleMessage(const Message& message){
	if (message.message == "pickedup"){
		this->_pickedUp = true;
		_mass = 10;
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
