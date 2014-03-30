#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Wall : public Entity {
private:
	btRigidBody* _rigidBody;
public:
	Wall(btRigidBody* body);
	~Wall() {}

	btRigidBody* getRigidBody() { return _rigidBody; }
	void setRigidBody(btRigidBody* value) { _rigidBody = value; }

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() {}
};