#include "Room.h"
#include "PhysicsEntity.h"
#include "Game.h"
#include "EntityManager.h"
#include "Wall.h"
#include <iostream>

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

Room::Room(std::string wallTexture, std::string floorTexture, std::string ceilingTexture, vector3df position, vector3df scale, array<int>* doors) : Entity(-1, 0, "Room"){
	_wallTexture = wallTexture;
	_floorTexture = floorTexture;
	_ceilingTexture = ceilingTexture;
	_position = position;
	_scale = scale;
	_doors = doors;
	EntityManager::registerEntity(this);
}

void Room::initialise() {

}

void Room::loadContent() {
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	_node->setPosition(_position);

	array<IMeshSceneNode*>* wallNodes = new array<IMeshSceneNode*>();
	wallNodes->set_used(4);

	PhysicsEntity* physicsEntity;

	vector3df currWallPos;
	vector3df lastWallPos(0,0,0);
	// preparing the walls
	for (u32 i = 0; i < 4; ++i) {
		wallNodes->push_back(game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f));
		physicsEntity = new PhysicsEntity(wallNodes->getLast(), "Wall");
		btRigidBody* body = PhysicsEngine::createBoxRigidBody(physicsEntity, _scale, 0.0f);
		// setting the position and scale of the walls
		if (i == 0) {
			wallNodes->getLast()->setPosition(_position + vector3df(0.0f, 0.0f, 0.0f));
			wallNodes->getLast()->setScale(_scale);
			body = PhysicsEngine::createBoxRigidBody(physicsEntity, _scale, 0.0f);
		}
		else if (i == 1) {
			wallNodes->getLast()->setPosition(_position + vector3df(_scale.Z, 0.0f, 0.0f));
			wallNodes->getLast()->setScale(vector3df(_scale.Z, _scale.Y, _scale.X));
			body = PhysicsEngine::createBoxRigidBody(physicsEntity, vector3df(_scale.Z, _scale.Y, _scale.X), 0.0f);
		}
		else if (i == 2) {
			wallNodes->getLast()->setPosition(_position + vector3df(_scale.X, 0.0f, _scale.Z));
			wallNodes->getLast()->setScale(vector3df(_scale.X, _scale.Y, -_scale.Z));
			body = PhysicsEngine::createBoxRigidBody(physicsEntity, vector3df(_scale.X, _scale.Y, -_scale.Z), 0.0f);
		}
		else if (i == 3) {
			wallNodes->getLast()->setPosition(_position + vector3df(_scale.Z, 0.0f, 0.0f));
			wallNodes->getLast()->setPosition(vector3df(-_scale.Z, _scale.Y, _scale.X));
			body = PhysicsEngine::createBoxRigidBody(physicsEntity, vector3df(-_scale.Z, _scale.Y, _scale.X), 0.0f);
		}
		// setting the texture
		wallNodes->getLast()->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_wallTexture.c_str()));
		// creating an entity from each wall
		Wall* entity = new Wall(body);
		entity->setName("Wall");
		entity->setNode(wallNodes->getLast());
		std::cout << "Here" << endl;
		// setting up the rigid body for the walls
		entity->setRigidBody(body);
		physicsEntity->setRigidBody(body);
	}

	// preparing the floor
	IMeshSceneNode* floorNode = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	floorNode->setPosition(_position + vector3df(_scale.Z/2, 0.0f, _scale.Z/2));
	floorNode->setScale(vector3df(_scale.Z, 1.0f, _scale.Z));
	floorNode->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_floorTexture.c_str()));

	// creating an entity for the floor
	physicsEntity = new PhysicsEntity(floorNode, "Floor");
	btRigidBody* floorBody = PhysicsEngine::createBoxRigidBody(physicsEntity, vector3df(_scale.Z, 1.0f, _scale.Z), 0.0f);

	Wall* floorEntity = new Wall(floorBody);
	floorEntity->setName("Floor");
	floorEntity->setNode(floorNode);

	// setting up the rigid body for the floor
	physicsEntity->setRigidBody(floorBody);

	// preparing the ceiling
	IMeshSceneNode* ceilingNode = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	ceilingNode->setPosition(_position + vector3df(_scale.Z / 2, _scale.Y, _scale.Z / 2));
	ceilingNode->setScale(vector3df(_scale.Z, 1.0f, _scale.Z));
	ceilingNode->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_ceilingTexture.c_str()));

	// creating an entity for the ceiling
	physicsEntity = new PhysicsEntity(ceilingNode, "Ceiling");
	btRigidBody* ceilingBody = PhysicsEngine::createBoxRigidBody(physicsEntity, vector3df(_scale.Z, 1.0f, _scale.Z), 0.0f);

	Wall* ceilingEntity = new Wall(ceilingBody);
	ceilingEntity->setName("Ceiling");
	ceilingEntity->setNode(ceilingNode);

	// setting up the rigid body for the ceiling
	physicsEntity->setRigidBody(ceilingBody);
}

void Room::update(float deltaTime) {

}

/*void Room::addObject(std::string name, std::string meshPath, std::string texturePath, btVector3 position, float mass) {

}*/