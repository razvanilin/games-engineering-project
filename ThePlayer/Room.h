#pragma once

#include "Entity.h"
#include "PhysicsEngine.h"
#include "Furniture.h"
#include "Object.h"
#include "Collectable.h"

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
	int _doors[4];
	int _exitDoor;
public:
	// when creating a room, specify the textures for walls, floor and ceiling
	
	/* the position is used to determine the lower left corner of the room
	 * the walls will be built from there, clockwise
	 */

	/* also, the constructor needs an array of int for determining where the doors are -
	 * door 1 = right; door 2 = left; door 3 = front; door 4 = back; other numbers are ignored
	 */

	/* using scale:
	 * X - wall thickness; Y - wall height; Z - wall width;
	 */
	
	Room(std::string name, std::string wallTexture, std::string floorTexture, std::string ceilingTexture, vector3df position, vector3df scale, int doors[4], int exitDoor);
	~Room(){}

	array<btRigidBody*>* getBounds() { return _bounds; }

	// will determine the dimensions of the walls, floor and ceiling
	vector3df getScale() { return _scale; }
	void setScale(vector3df value) { _scale = value; }

	vector3df getPosition() { return _position; }
	void setPosition(vector3df value) { _position = value; }

	std::string getName() { return _name; }

	// add an object in the room
	void loadDoors();

	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent() {}

	Furniture* addFurniture(std::string name, std::string roomName, std::string meshPath, vector3df position, vector3df scale, float mass);
	void placeObject(Object* object, vector3df position);
	void placeCollectable(Collectable* collectable, vector3df position);

};