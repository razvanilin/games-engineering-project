#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Door : public Entity {
private:
	btRigidBody* _rigidBody;
	bool _isExit;
	int _direction;
	vector3df _position;
	vector3df _scale;

public:
	Door(vector3df position, vector3df scale, int _direction, bool isExit);
	~Door() { }

	btRigidBody* getRigidBody() { return _rigidBody; }
	void setRigidBody(btRigidBody* value) { _rigidBody = value; }

	int getDirection() { return _direction; }

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() { }
};