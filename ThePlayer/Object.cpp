#include "Object.h"
#include "Game.h"
#include "EntityManager.h"
#include "Player.h"
#include "FreeCamera.h"
#include "PhysicsEntity.h"
#include <iostream>

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an pickupable object. Initialises Entity and SM
Object::Object() : Entity(-1, 0, "Object"){
	_pickedUp = false;
	_name = "";
}


void Object::initialise(){
	Entity* player = EntityManager::getNamedEntities("Player")->front();
}

//Load content for the Object
void Object::loadContent(){
	//make a sphere
	//IMesh* mesh = game.getDevice()->getSceneManager()->getMesh("meshes/house/Shelve.obj")->getMesh(0);
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(0.3f);
	//_node->setScale(vector3df(0.1f, 0.1f, 0.1f));
	//_node->setMesh(mesh);
	//set position to (0,0,0)
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	//set material properties
	//_node->setVisible(0);
	_node->setMaterialFlag(EMF_LIGHTING, false);
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/fish.jpg"));
	//create rigid body (sphere with rad of 1)

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(1.0f, 1.0f, 1.0f), 10);
	//btCollisionShape *shape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));
	//_rigidBody->setCollisionShape(shape);

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
	}
	if (message.message == "dropped"){
		_rigidBody->activate();
		this->_pickedUp = false;
		

	}

}
