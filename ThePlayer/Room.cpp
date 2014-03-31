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
	Wall* wallEntity;
	btTransform trans;
	btQuaternion quat;
	btVector3 position = btVector3(_position.X, _position.Y, _position.Z);
	// preparing the walls
	for (u32 i = 0; i < 4; ++i) {
		wallNodes->push_back(game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f));
		//physicsEntity = new PhysicsEntity(wallNodes->getLast(), "Wall");
		wallEntity = new Wall();
		// setting the texture
		wallNodes->getLast()->setMaterialFlag(EMF_LIGHTING, false);
		wallNodes->getLast()->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_wallTexture.c_str()));
		// creating an entity from each wall
		wallEntity->setName("Wall");
		wallEntity->setNode(wallNodes->getLast());
		wallEntity->getNode()->setPosition(vector3df(position.x(), position.y(), position.z()));
		wallEntity->getNode()->setScale(_scale);
		// setting the position and scale of the walls
		if (i == 0) {
			wallEntity->getNode()->setPosition(_position);
			wallEntity->getNode()->setScale(_scale);
			btRigidBody* body = PhysicsEngine::createBoxRigidBody(wallEntity, _scale, 0.0f);
			wallEntity->setRigidBody(body);
		}
		else if (i == 1) {
			wallEntity->getNode()->setPosition(_position + vector3df(_scale.Z / 2 - _scale.X / 2, 0.0f, _scale.Z / 2));
			wallEntity->getNode()->setScale(vector3df(_scale.Z, _scale.Y, _scale.X));
			btRigidBody* body = PhysicsEngine::createBoxRigidBody(wallEntity, vector3df(_scale.Z, _scale.Y, _scale.X), 0.0f);
			wallEntity->setRigidBody(body);
		}
		else if (i == 2) {
			wallEntity->getNode()->setPosition(_position + vector3df(_scale.Z, 0.0f, _scale.X / 2));
			wallEntity->getNode()->setScale(vector3df(_scale.X, _scale.Y, -_scale.Z));
			btRigidBody* body = PhysicsEngine::createBoxRigidBody(wallEntity, vector3df(_scale.X, _scale.Y, _scale.Z), 0.0f);
			wallEntity->setRigidBody(body);
		}
		else if (i == 3) {
			wallEntity->getNode()->setPosition(_position + vector3df(_scale.Z / 2, 0.0f, -_scale.Z / 2));
			wallEntity->getNode()->setScale(vector3df(-_scale.Z - _scale.X, _scale.Y, -_scale.X));
			btRigidBody* body = PhysicsEngine::createBoxRigidBody(wallEntity, vector3df(_scale.Z - _scale.X, _scale.Y, -_scale.X), 0.0f);
			wallEntity->setRigidBody(body);
		}
	}

	// preparing the floor
	IMeshSceneNode* floorNode = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	floorNode->setPosition(_position + vector3df(_scale.Z / 2, -_scale.Y / 2 + _scale.X / 2, 0.0f));
	floorNode->setScale(vector3df(_scale.Z + _scale.X, 1.0f, _scale.Z + _scale.X));
	floorNode->setMaterialFlag(EMF_LIGHTING, false);
	floorNode->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_floorTexture.c_str()));

	// creating an entity for the floor
	//physicsEntity = new PhysicsEntity(floorNode, "Floor");

	Wall* floorEntity = new Wall();
	floorEntity->setName("Floor");
	floorEntity->setNode(floorNode);

	btRigidBody* floorBody = PhysicsEngine::createBoxRigidBody(floorEntity, vector3df(_scale.Z, 0.5f, _scale.Z), 0.0f);
	floorBody->setFriction(1.5f);
	floorEntity->setRigidBody(floorBody);

	// preparing the ceiling
	IMeshSceneNode* ceilingNode = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	ceilingNode->setPosition(_position + vector3df(_scale.Z / 2, _scale.Y/2 + _scale.X, 0.0f));
	ceilingNode->setScale(vector3df(_scale.Z, 1.0f, _scale.Z));
	ceilingNode->setMaterialFlag(EMF_LIGHTING, false);
	ceilingNode->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(_ceilingTexture.c_str()));

	// creating an entity for the ceiling
	//physicsEntity = new PhysicsEntity(ceilingNode, "Ceiling");

	Wall* ceilingEntity = new Wall();
	ceilingEntity->setName("Ceiling");
	ceilingEntity->setNode(ceilingNode);

	btRigidBody* ceilingBody = PhysicsEngine::createBoxRigidBody(ceilingEntity, vector3df(_scale.Z, 1.0f, _scale.Z), 0.0f);
	ceilingEntity->setRigidBody(ceilingBody);

	// setting up the rigid body for the ceiling
	//physicsEntity->setRigidBody(ceilingBody);
}

void Room::update(float deltaTime) {

}

/*void Room::addObject(std::string name, std::string meshPath, std::string texturePath, btVector3 position, float mass) {

}*/