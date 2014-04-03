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
	vector3df _forward;
	vector3df _up;
	float _mod;
	vector3df _startPos;
	std::string _itemName;
	std::string _currentRoom;

public:
	//constructor
	Object(std::string name, vector3df startPos);
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
	//getsets for current room
	std::string getCurrentRoom() { return _currentRoom; }
	void setCurrentRoom(std::string value) { _currentRoom = value; }


	vector3df getUp() { return _up; }
	void setUp(vector3df value) { _up = value; }

	vector3df getForward() { return _forward; }
	void setForward(vector3df value) { _forward = value; }

	std::string getItemName(){
		return _itemName;
	}

	void Object::handleMessage(const Message& message);
};