/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Door.h"
#include "PhysicsEntity.h"
#include "EntityManager.h"
#include "HudManager.h"
#include "Game.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

Door::Door(vector3df position, vector3df scale, int direction, bool isExit) : Entity(-1, 0, "Door") {
	_position = position;
	_scale = scale;
	_direction = direction;
	_isExit = isExit;
}

void Door::initialise() {

}

void Door::loadContent() {
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setPosition(_position);
	_node->setScale(_scale);
	_node->setMaterialFlag(EMF_LIGHTING, false);
	if (_isExit)
		_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/externaldoor.jpg"));
	else
		_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/internaldoor.png"));
	
	_rigidBody = PhysicsEngine::createBoxRigidBody(this, _scale, 0.0f);
	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Door");
	physicsEntity->setRigidBody(_rigidBody);
}

void Door::update(float deltaTime) {
	HudManager* hudMan = (HudManager*)EntityManager::getNamedEntities("Hudman")->front();
	if (!hudMan->hasHintBeenShownFor("Door")){
		Entity* player = EntityManager::getNamedEntities("Player")->front();
		vector3df playerPos = player->getNode()->getPosition();
		vector3df objectPos = _node->getPosition();
		vector3df d = playerPos - objectPos;
		auto dist = d.getLength();
		if (d.getLength()<5){
			hudMan->drawHintFor("Door");
		}
	}
}