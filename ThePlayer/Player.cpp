#include "Player.h"
#include "Game.h"

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

void Player::initialise(){

}

void Player::loadContent(){
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	_node->setMaterialFlag(EMF_LIGHTING, false);
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("checked.jpg"));
}

void Player::update(float deltaTime){
	float mod = 5.0f;

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
}