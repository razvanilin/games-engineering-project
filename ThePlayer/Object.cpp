#include "Object.h"
#include "Game.h"
#include "EntityManager.h"

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
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(10);
	//set position to (0,0,0)
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	//set material properties
	_node->setMaterialFlag(EMF_LIGHTING, false);
	
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/fish.jpg"));
	//create rigid body (sphere with rad of 1)
	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(1.0f, 1.0f, 1.0f), 10);
}

//updates the Object
void Object::update(float deltaTime){
	//if object is picked up - it's position is fixed to the player
	if (_pickedUp){
		btRigidBody* body = getRigidBody();
		Entity* player = EntityManager::getNamedEntities("Player")->front();
		vector3df playerPos = player->getNode()->getPosition();
		this->_node->setPosition(playerPos + vector3df(0.0f, 1.0f, 0.0f));
		btVector3 newPos = btVector3(playerPos.X, playerPos.Y+1.0f, playerPos.Z);
		btTransform transform = this->getRigidBody()->getCenterOfMassTransform();
		transform.setOrigin(newPos);
		body->setCenterOfMassTransform(transform);		
	}
	else{
		// update our position and orientation from PhysicsEngines rigid body
		btVector3 point = _rigidBody->getCenterOfMassPosition();
		_node->setPosition(vector3df(point.getX(), point.getY(), point.getZ()));		
	}
}

void Object::handleMessage(const Message& message){
	if (message.message == "pickedup"){
		this->_pickedUp = true;
	}

	if (message.message == "thrown"){
		_rigidBody->activate();
		this->_pickedUp = false;
		_rigidBody->setLinearVelocity(btVector3(10.0f, 10.0f, 0.0f));
		
	}
	if (message.message == "dropped"){
		_rigidBody->activate();
		this->_pickedUp = false;
		

	}

}
