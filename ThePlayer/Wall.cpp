/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Wall.h"
#include "EntityManager.h"
#include "PhysicsEntity.h"
#include "Game.h"

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

Wall::Wall() : Entity(-1, 0, "Wall") {
	
}

void Wall::initialise() {

}

void Wall::loadContent() {
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(.0f);
	_node->setPosition(vector3df(0, 0, 0));
	_node->setMaterialFlag(EMF_LIGHTING, false);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Wall");
	physicsEntity->setRigidBody(_rigidBody);
}

void Wall::update(float deltaTime) {

}

