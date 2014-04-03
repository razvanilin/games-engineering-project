#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Furniture : public Entity {
private:
	btRigidBody* _rigidBody;
	vector3df _position;
	vector3df _scale;
	std::string _name;
	std::string _roomName;
	std::string _mesh;
	float _mass;
	btVector3* _rotationAxis;
	btScalar _rotationAngle;

public:
	// name is also used to find the right folder inside the mesh assets
	Furniture(std::string name, std::string roomName, std::string meshPath, vector3df position, vector3df scale, float mass);
	~Furniture() {}

	btRigidBody* getRigidBody() { return _rigidBody; }
	void setRigidBody(btRigidBody* value) { _rigidBody = value; }

	vector3df getPosition() { return _position; }
	vector3df getScale() { return  _scale; }

	void setRotationAxis(btVector3* value) { _rotationAxis = value; }
	void setRotationAngle(btScalar value) { _rotationAngle = value; }

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() {}
};