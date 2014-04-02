#include "Collectable.h"
#include "Game.h"
#include "EntityManager.h"
#include <iostream>
#include "Player.h"
#include "PhysicsEntity.h"
#include "MessageHandler.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an pickupable object. Initialises Entity and SM
Collectable::Collectable(std::string name, vector3df startPos) : Entity(-1, 0, "Collectable"){
	_itemName = name;
	_startPos = startPos;
}


void Collectable::initialise(){

}

//Load content for the Object
void Collectable::loadContent(){

	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1);
	//set position to (0,0,0)
	_node->setPosition(_startPos);

	//set material properties
	_node->setMaterialFlag(EMF_LIGHTING, false);
	std::string pathToTexture = "textures/" + _itemName + ".jpg";
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(pathToTexture.c_str()));
	_alive = true;

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(0.5f, 0.5f, 0.5f), 10.0f);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Collectable");
	physicsEntity->setRigidBody(_rigidBody);
}

//updates the Object
void Collectable::update(float deltaTime){


}

void Collectable::handleMessage(const Message& message){
	if (message.message == "COLLISION"){
		if (((Entity*)message.data)->getName() == "Player"){
			Player* player = (Player*)message.data;
			_alive = false;
			_node->setVisible(false);

			//send message to player that item has been picked up
			Message m(player, "pickup", this);
			MessageHandler::sendMessage(m);
		}
	}

}
