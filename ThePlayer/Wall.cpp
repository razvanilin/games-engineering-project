#include "Wall.h"
#include "EntityManager.h"
#include "PhysicsEntity.h"
#include "Game.h"

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

Wall::Wall(btRigidBody* body) : Entity(-1, 0, "Wall") {
	_rigidBody = body;
}

void Wall::initialise() {

}

void Wall::loadContent() {
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setPosition(vector3df(0, 0, 0));
	_node->setMaterialFlag(EMF_LIGHTING, false);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Wall");
	physicsEntity->setRigidBody(_rigidBody);
}

void Wall::update(float deltaTime) {

}
