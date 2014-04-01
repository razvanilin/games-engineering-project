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
}

void Player::update(float deltaTime){
	float mod = 10.0f;

	if (inputHandler.isKeyDown(KEY_KEY_W)){
		_node->setPosition(_node->getPosition() + (vector3df(0.0f, 0.0f, -1.0f)*deltaTime*mod));
	}
	if (inputHandler.isKeyDown(KEY_KEY_S)){
		_node->setPosition(_node->getPosition() + (vector3df(0.0f, 0.0f, 1.0f)*deltaTime*mod));
	}
	if (inputHandler.isKeyDown(KEY_KEY_A)){
		_node->setPosition(_node->getPosition() + (vector3df(1.0f, 0.0f, 0.0f)*deltaTime*mod));
	}
	if (inputHandler.isKeyDown(KEY_KEY_D)){
		_node->setPosition(_node->getPosition() + (vector3df(-1.0f, 0.0f, 0.0f)*deltaTime*mod));
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