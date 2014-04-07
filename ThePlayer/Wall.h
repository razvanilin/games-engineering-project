/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Wall : public Entity {
private:
	btRigidBody* _rigidBody;
public:
	Wall();
	~Wall() {}

	btRigidBody* getRigidBody() { return _rigidBody; }
	void setRigidBody(btRigidBody* value) { _rigidBody = value; }

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() {}
};