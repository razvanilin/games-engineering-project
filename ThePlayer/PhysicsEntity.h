/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once
#include "Entity.h"
#include <btBulletcollisionCommon.h>

using namespace GameEngine;
using namespace irr::scene;

class PhysicsEntity : public Entity{
private:
	//represents a physical object
	btRigidBody* _rigidBody;
public:
	PhysicsEntity(ISceneNode* node, const std::string& name) : Entity (-1, node, name){}
	~PhysicsEntity(){}

	//getter and setter for _rigidbody
	void setRigidBody(btRigidBody* val){_rigidBody = val;}
	btRigidBody* getRigidBody(){return _rigidBody;}

	void initialise(){}
	void loadContent(){}
	void update (float deltaTime);
	void unloadContent(){}
	void handleMessage(const Message& message);
};