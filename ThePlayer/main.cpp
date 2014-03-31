//add Irrlicht
#pragma comment (lib, "Irrlicht")

#include <Irrlicht.h>
#include <iostream>
#include "Game.h"
#include "TargetCamera.h"
#include "PhysicsEntity.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Object.h"
#include "Enemy.h"
#include "FreeCamera.h"
#include "Room.h"


using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

// function header to add a box to our game world
btRigidBody* createBox(const std::string& name, const vector3df& position, const vector3df& scale, float mass);
//function header to add a sphere
void createSphere(const std::string& name, const vector3df& position, float radius, float mass);


int main (){
	Player* player = new Player();

	Object* tester = new Object();

	Room* room = new Room("textures/steel.jpg", "textures/flame.jpg", "textures/checked.jpg", vector3df(-2.0f, 0.5, -2.0f), vector3df(.5f, 6.5f, 10.0f), new array<int>());

	Enemy* enemies[5];
	for (int i = 0; i<5; i++){
		enemies[i] = new Enemy();
	}

	//setup window
	game.setCaption(L"State Machines");
	game.setDimensions(dimension2d<u32>(1366,768));

	//add a camera
	FreeCamera* cam = new FreeCamera();
	cam->setPosition(vector3df(0.0f,30.0f,30.0f));
	cam->setTarget(vector3df(0.0f,0.0f,0.0f));
	cam->setYaw(0.0f);
	cam->setPitch(0.0f);
	game.setCam(cam);

	//initialise and load content
	if(!game.initialise()) return -1;
	if(!game.loadContent()) return -1;

	//create a floor
	//btRigidBody* floor = createBox("Floor", vector3df(0.0f, -5.0f, 0.0f), vector3df(50.0f, 0.5f, 50.0f), 0.0f);

	//create a wall
	//createBox("Wall", vector3df(25.0f, 0.0f, 0.0f), vector3df(0.5f, 10.0f, 50.0f), 0.0f);
	//createBox("Wall", vector3df(-25.0f, 0.0f, 0.0f), vector3df(0.5f, 10.0f, 50.0f), 0.0f);

	//set up timers
	u32 prevTime = game.getDevice()->getTimer()->getRealTime();
	u32 currTime;
	float deltaTime;
	int mod = 0;
	btTransform transform;

	while(game.getDevice()->run()){
		//update timers
		currTime = game.getDevice()->getTimer()->getRealTime();
		deltaTime = float (currTime - prevTime)/1000.0f;

		//escape!
		if (inputHandler.isKeyDown(KEY_ESCAPE)){
			break;
		}

		// zoom in or out so you can see the player
		if (inputHandler.isKeyDown(KEY_PLUS) && !inputHandler.wasKeyDown(KEY_PLUS)) {
			mod++;
		}
		if (inputHandler.isKeyDown(KEY_MINUS) && !inputHandler.wasKeyDown(KEY_MINUS)) {
			mod--;
		}
		
		// resets the position and velocity of the object object
		if (inputHandler.isKeyDown(KEY_KEY_1) && !inputHandler.wasKeyDown(KEY_KEY_1)) {
			//tester->~Object();
			transform = tester->getRigidBody()->getCenterOfMassTransform();
			transform.setOrigin(btVector3(player->getNode()->getPosition().X, player->getNode()->getPosition().Y+1, player->getNode()->getPosition().Z));
			tester->getRigidBody()->setCenterOfMassTransform(transform);
			tester->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		}

		// set the camera position so it follows the player
		cam->setPosition(vector3df(player->getNode()->getPosition().X, player->getNode()->getPosition().Y+0.5f, player->getNode()->getPosition().Z+mod));

		// stealth movement -> lower the camera a bit and update the player status
		if (inputHandler.isKeyDown(KEY_LCONTROL)) {
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y - .1f, cam->getPosition().Z));
			player->setStealth(true);
		}
		else if (player->isStealthActive()){
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y + .1f, cam->getPosition().Z));
			player->setStealth(false);
		}

		if (player->getNode()->getPosition().Y > room->getNode()->getPosition().Y - room->getNode()->getScale().Y) {
			player->setDown(false);
		}
		else
			player->setDown(true);
		// Now check if the mouse has moved
		int deltaX = inputHandler.getCurrentMouse().Position.X - inputHandler.getPrevMouse().Position.X;
		int deltaY = inputHandler.getCurrentMouse().Position.Y - inputHandler.getPrevMouse().Position.Y;
		// Rotate the camera by the change in the mouse position. 
		player->rotate(deltaX * deltaTime, deltaY * deltaTime);
		cam->rotate(deltaX * deltaTime, deltaY * deltaTime);

		//update
		if(!game.update(deltaTime)) break;

		//render
		if(!game.render()) break;

		prevTime = currTime;
	}

	//game ended unload and shutdown
	game.unloadContent();
	// shutdown game
	game.shutdown();
}


// function to add a box to our game world
btRigidBody* createBox(const std::string& name, const vector3df& position, const vector3df& scale, float mass){
	//first create a box using Irrlicht
	IMeshSceneNode* node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
	// and set the scale
	node->setScale(scale);
	//set the position
	node->setPosition(position);
	// Set the material properties Use a texture of your choice
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/steel.jpg"));

	//create a PhysicsEntity
	PhysicsEntity* physicsEntity = new PhysicsEntity(node, name);
	//create the rigidBody for the entity
	btRigidBody* body = PhysicsEngine::createBoxRigidBody(physicsEntity, scale, mass);
	body->setFriction(1.5f);
	body->setRollingFriction(2.0f);
	physicsEntity->setRigidBody(body);

	return body;
}

void createSphere(const std::string& name, const vector3df& position, float radius, float mass){
	//create sphere geometry
	IMeshSceneNode* node  = game.getDevice()->getSceneManager()->addSphereSceneNode(radius, 32);

	//and again
	node->setPosition(position);
	//set material properties
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/checked.jpg"));

	//create a PhysicsEntity
	PhysicsEntity* physicsEntity = new PhysicsEntity(node, name);
	//create the rigidBody for the entity
	btRigidBody* rigidBody = PhysicsEngine::createSphereRigidBody(physicsEntity, radius, mass);

	//sets its velocity towards the wall with a random Z value
	rigidBody->setLinearVelocity(btVector3(-20.0f, 0.0f, -5.0f + (rand()%10)));
	//add the rigidBody to the PhysicsEntity
	physicsEntity->setRigidBody(rigidBody);
	
}