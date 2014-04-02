#include "Collectable.h"
#include "Game.h"
#include "EntityManager.h"
#include <iostream>
#include "Player.h"

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

}

//updates the Object
void Collectable::update(float deltaTime){
	

	if (this->isAlive()){
		Player* player = (Player*)EntityManager::getNamedEntities("Player")->front();
		vector3df toTarget = player->getNode()->getPosition() - _node->getPosition();
					
		irr::core::aabbox3df pb = player->getNode()->getTransformedBoundingBox();
		irr::core::aabbox3df cb = _node->getTransformedBoundingBox();
			
		//if (pb.intersectsWithBox(cb)){
		if (toTarget.getLength()<1.0f){
			_alive = false;
			_node->setVisible(false);
			player->addItem(_itemName);
			cout << this->getItemName() << " picked up" << endl;
		}
	}
}

void Collectable::handleMessage(const Message& message){


}
