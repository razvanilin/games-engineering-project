#include "Room.h"
#include "PhysicsEntity.h"
#include "Game.h"
#include "EntityManager.h"
#include "Wall.h"
#include "Door.h"
#include <iostream>

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

void constructDoor(vector3df position, vector3df scale, int direction, bool isExit);
void constructWall(vector3df position, vector3df scale, std::string texture);

Room::Room(std::string name, std::string wallTexture, std::string floorTexture, std::string ceilingTexture, vector3df position, vector3df scale, int doors[4], int exitDoor) : Entity(-1, 0, "Room"){
	_wallTexture = wallTexture;
	_floorTexture = floorTexture;
	_ceilingTexture = ceilingTexture;
	_position = position;
	_scale = scale;
	_name = name;
	for (int i = 0; i < 4; ++i) {
		_doors[i] = doors[i];
	}
	_exitDoor = exitDoor;
	EntityManager::registerEntity(this);
}

void Room::initialise() {

}

void Room::loadContent() {
	_node = game.getDevice()->getSceneManager()->addCubeSceneNode(.0f);
	_node->setPosition(_position);

	// preparing the walls
	for (int i = 0; i < 4; ++i) {

		if (i == 0){
			constructWall(
				vector3df(_position.X+_scale.Z/2, _position.Y, _position.Z), 
				vector3df(_scale.X, _scale.Y, _scale.Z),
				_wallTexture);
		}
		else if (i == 1) {
			constructWall(
				vector3df(_position.X-_scale.Z/2, _position.Y, _position.Z), 
				vector3df(_scale.X, _scale.Y, _scale.Z), 
				_wallTexture);
		}
		else if (i == 2) {
			constructWall(
				vector3df(_position.X, _position.Y, _position.Z + _scale.Z / 2),
				vector3df(_scale.Z, _scale.Y, _scale.X), 
				_wallTexture);
		}
		else {
			constructWall(
				vector3df(_position.X, _position.Y, _position.Z - _scale.Z / 2),
				vector3df(_scale.Z, _scale.Y, _scale.X), 
				_wallTexture);
		}
	}
	
	// preparing the floor
	constructWall(
		vector3df(_position.X, _position.Y - _scale.Y/2, _position.Z), 
		vector3df(_scale.Z, _scale.X, _scale.Z),
		_floorTexture);
	
	// preparing the ceiling
	constructWall(
		vector3df(_position.X, _scale.Y/2, _position.Z), 
		vector3df(_scale.Z, _scale.X, _scale.Z), 
		_ceilingTexture);
	
	// loading the doors
	loadDoors();
}

void constructWall(vector3df position, vector3df scale, std::string texture) {
	// will construct a wall based on the passed information
	ISceneNode* wallNode = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	wallNode->setPosition(position);
	wallNode->setScale(scale);
	wallNode->setMaterialFlag(EMF_LIGHTING, false);
	wallNode->setAutomaticCulling(EAC_OFF);
	wallNode->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture(texture.c_str()));

	Wall* wallEntity = new Wall();
	wallEntity->setName("Wall");
	wallEntity->setNode(wallNode);

	btRigidBody* wallBody = PhysicsEngine::createBoxRigidBody(wallEntity, wallEntity->getNode()->getScale(), 0.0f);
	wallBody->setFriction(1.5f);
	wallEntity->setRigidBody(wallBody);
}

// will load the doors based on the array of ints
// 1 = right; 2 = left; 3 = front; 4 = back; the other numbers are ignored
void Room::loadDoors() {
	for (int i = 0; i < 4; ++i) {
		std::cout << _doors[i] << std::endl;
		// if valid number found, call construct door which creates the door entity
		// also check if the door is the exit
		if (_doors[i] == 1) {
			bool isExit = false;
			if (_exitDoor == 1)
				isExit = true;

			new Door(
				vector3df(_position.X + _scale.Z / 2 - _scale.X/2, _position.Y - _scale.Y / 4 + _scale.X, _position.Z),
				vector3df(_scale.X, _scale.Y / (_scale.Y / 4) + _scale.X, 2.0f),
				1,
				isExit
				);
		}
		else if (_doors[i] == 2) {
			bool isExit = false;
			if (_exitDoor == 2)
				isExit = true;

			new Door(
				vector3df(_position.X - _scale.Z / 2 + _scale.X/2, _position.Y - _scale.Y / 4 + _scale.X, _position.Z),
				vector3df(_scale.X, _scale.Y / (_scale.Y / 4) + _scale.X, 2.0f),
				2,
				isExit
				);
		}
		else if (_doors[i] == 3) {
			bool isExit = false;
			if (_exitDoor == 3)
				isExit = true;

			new Door(
				vector3df(_position.X, _position.Y - _scale.Y / 4 + _scale.X, _position.Z + _scale.Z / 2 - _scale.X/2), 
				vector3df(2.0f, _scale.Y / (_scale.Y/4) + _scale.X, _scale.X/2),
				3,
				isExit
				);
		}
		else if (_doors[i] == 4) {
			bool isExit = false;
			if (_exitDoor == 4)
				isExit = true;

			new Door(
				vector3df(_position.X, _position.Y - _scale.Y / 4 + _scale.X, _position.Z - _scale.Z / 2 + _scale.X/2), 
				vector3df(2.0f, _scale.Y / (_scale.Y/4) + _scale.X, _scale.X),
				4,
				isExit
				);
		}
	}
}

void constructDoor(vector3df position, vector3df scale, int direction, bool isExit) {
	new Door(position, scale, direction, isExit);
}

void Room::update(float deltaTime) {

}

void Room::addObject(std::string name, std::string meshPath, std::string texturePath, btVector3* position, float mass) {

}