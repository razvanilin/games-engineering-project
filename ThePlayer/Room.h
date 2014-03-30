#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"

using namespace GameEngine;

class Room : public Entity {
private:
	array<btRigidBody*>* _bounds;
	vector3df _scale;
	vector3df _position;
	std::string _name;
	std::string _wallTexture;
	std::string _floorTexture;
	std::string _ceilingTexture;
	array<int>* _doors;
public:
	// when creating a room, specify the textures for walls, floor and ceiling
	

	/* the position is used to determine the lower left corner of the room
	 * the walls will be built from there, clockwise
	 */

	/* also, the constructor needs an array of int for determining where the doors are -
	 * door 1 for example will be the front door and the others will be determined clockwise
	 * usage: "array(1,3,4)" - will create a door forward, backwards and to the left
	 */

	Room(std::string wallTexture, std::string floorTexture, std::string ceilingTexture, vector3df position, vector3df scale, array<int>* doors);
	~Room(){}

	array<btRigidBody*>* getBounds() { return _bounds; }

	// will determine the dimensions of the walls, floor and ceiling
	vector3df getScale() { return _scale; }
	void setScale(vector3df value) { _scale = value; }

	vector3df getPosition() { return _position; }
	void setPosition(vector3df value) { _position = value; }

	// add an object in the room
	//void addObject(std::string name, std::string meshPath, std::string texturePath, btVector3 position, float mass);

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() {}
};