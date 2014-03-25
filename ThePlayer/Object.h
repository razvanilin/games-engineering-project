#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Object : public Entity{
private:
	//Rigidbody controlling movement (physics)
	btRigidBody* _rigidBody;
	//boolean indicating if object has been collected
	bool _pickedUp;
	std::string _name;

public:
	//constructor
	Object();
	//destructor
	~Object(){}
	//RB getter
	btRigidBody* getRigidBody(){ return _rigidBody; }
	//initialise
	void initialise();
	//Loads any content
	void loadContent();
	//Updates enemy
	void update(float deltaTime);
	//Unloads anything not handled by Irrlicht or Bullet
	void unloadContent(){}
	//getter for pickedUp
	bool getPickedUp(){ return _pickedUp; }
	//setter for pickedUp
	void setPickedUp(bool val){ _pickedUp = val; }

	void Object::handleMessage(const Message& message);
};