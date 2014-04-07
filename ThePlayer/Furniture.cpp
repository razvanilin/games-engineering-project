/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Furniture.h"
#include "PhysicsEntity.h"
#include "Game.h"
#include <sstream>
#include <iostream>

using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

Furniture::Furniture(std::string name, std::string roomName, std::string meshPath, vector3df position, vector3df scale, float mass) : Entity(-1, 0, "Furniture") {
	_name = name;
	_roomName = roomName;
	_mesh = meshPath;
	_position = position;
	_scale = scale;
	_mass = mass;
	_rotationAngle = 0;
	_rotationAxis = new btVector3(1, 1, 1);
}

void Furniture::initialise() {

}

void Furniture::loadContent() {
	IAnimatedMesh* mesh = 0;
	std::wstringstream path;
	path << "meshes/" << _name.c_str() << "/" <<  _mesh.c_str();
	mesh = game.getDevice()->getSceneManager()->getMesh(path.str().c_str());
	if (!mesh){
		std::cout << "Could not load " << _mesh.c_str() << " mesh" << std::endl;
		return;
	}
	_node = game.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(mesh);

	_node->setPosition(_position);
	_node->setMaterialFlag(EMF_LIGHTING, false);
	_node->setScale(_scale);

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(2.0f, 2.0f, 2.0f), _mass);
	btQuaternion quat;
	quat.setRotation(*_rotationAxis, _rotationAngle);
	btTransform trans = _rigidBody->getCenterOfMassTransform();
	trans.setRotation(quat);
	_rigidBody->setCenterOfMassTransform(trans);
	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, _name);
	physicsEntity->setRigidBody(_rigidBody);
}

void Furniture::update(float deltaTime) {

}