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
#include "Collectable.h"
#include <sstream>
#include <IGUIFont.h>


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

<<<<<<< HEAD
	Object* fish = new Object("fish", vector3df(-15.0f, 0.0f, 5.0f));
	Object* spray = new Object("spray", vector3df(-15.0f, 0.0f, 15.0f));
	Object* carrot = new Object("carrot", vector3df(-15.0f, 0.0f, -15.0f));
	Object* bone = new Object("bone", vector3df(15.0f, 0.0f, -15.0f));

	Collectable* socks = new Collectable("socks", vector3df(-10.0f, 0.0f, -10.0f));
	Collectable* jeans = new Collectable("jeans", vector3df(10.0f, 0.0f, 10.0f));
	Collectable* shoes = new Collectable("shoes", vector3df(-10.0f, 0.0f, 10.0f));
	Collectable* shirt = new Collectable("shirt", vector3df(10.0f, 0.0f, -10.0f));
=======
	Object* fish = new Object("fish", vector3df(0.0f, 0.0f, 0.0f));//leave there
	Object* spray = new Object("spray", vector3df(-15.0f, 0.0f, 15.0f));//leave there
	Object* carrot = new Object("carrot", vector3df(15.0f, 0.0f, 10.0f));//t
	Object* bone = new Object("bone", vector3df(0.0f, 0.0f, 15.0f));//t

	Collectable* socks = new Collectable("socks", vector3df(-5.5f, 0.0f, 35.5f));
	Collectable* jeans = new Collectable("jeans", vector3df(-20.0f, 0.0f, 24.5f));
	Collectable* shoes = new Collectable("shoes", vector3df(-20.0f, 0.0f, 20.0f));
	Collectable* shirt = new Collectable("shirt", vector3df(20.5f, 0.0f, 9.25f));
>>>>>>> eb236c080a83e866b47b64f67903d66407a63396

	Room* bedroom		= new Room("Bedroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{1,3}, 1);
	Room* hall			= new Room("Hall", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 15.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{1, 2, 3, 4}, 0);
	Room* bathroom		= new Room("Bathroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(15.0f, 0.0f, 15.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{2}, 0);
	Room* storageroom	= new Room("Storageroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(-15.0f, 0.0f, 15.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{1}, 0);
	Room* livingroom	= new Room("Livingroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 30.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{1, 2, 4}, 0);
	Room* kitchen		= new Room("Kitchen", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(15.0f, 0.0f, 30.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{2, 3}, 0);
	Room* depo			= new Room("Depo", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(15.0f, 0.0f, 30.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{4}, 0);
	Room* hallexit		= new Room("Hallexit", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(-15.0f, 0.0f, 30.0f), vector3df(.5f, 7.5f, 15.0f), new int[]{1, 2}, 2);

<<<<<<< HEAD
	Enemy* fatcat = new Enemy("fatcat", vector3df(10.0f, 0.0f, 10.0f), 5.0f);
	Enemy* cat = new Enemy("cat", vector3df(-10.0f, 0.0f, -10.0f), 10.0f);
	Enemy* dog = new Enemy("dog", vector3df(-10.0f, 0.0f, 10.0f), 10.0f);
	Enemy* rabbit = new Enemy("rabbit", vector3df(10.0F, 0.0F, -10.0F), 10.0f);
=======
	Enemy* fatcat = new Enemy("fatcat", vector3df(20.0f, 0.0f, 10.0f), 5.0f, fish, shirt);
	Enemy* cat = new Enemy("cat", vector3df(-5.0f, 0.0f, 34.0f), 5.0f, spray, socks);
	Enemy* dog = new Enemy("dog", vector3df(-20.0f, 0.0f, 20.0f), 10.0f, bone, shoes);
	Enemy* rabbit = new Enemy("rabbit", vector3df(-20, 0.0F, 25.0F), 10.0f, carrot, jeans);
>>>>>>> eb236c080a83e866b47b64f67903d66407a63396

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

	irr::gui::IGUIStaticText* text;
	irr::gui::IGUIEnvironment* guienv = game.getDevice()->getGUIEnvironment();
	text = guienv->addStaticText(L"0 : 0", irr::core::rect<irr::s32>(250, 10, 1000, 200), false);
	irr::gui::IGUIFont* font = guienv->getFont("bigfont.png");
	text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	text->setOverrideFont(font);


	//set up timers
	u32 prevTime = game.getDevice()->getTimer()->getRealTime();
	u32 currTime;
	float deltaTime;
	int mod = 0;
	btTransform transform;
	//player->getNode()->setPosition(vector3df(0, 100, 0));
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
		/*if (inputHandler.isKeyDown(KEY_KEY_1) && !inputHandler.wasKeyDown(KEY_KEY_1)) {
			//tester->~Object();
			transform = tester->getRigidBody()->getCenterOfMassTransform();
			transform.setOrigin(btVector3(player->getNode()->getPosition().X, player->getNode()->getPosition().Y, player->getNode()->getPosition().Z));
			tester->getRigidBody()->setCenterOfMassTransform(transform);
			tester->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		}*/

		// set the camera position so it follows the player
		btVector3 playerPos = player->getRigidBody()->getCenterOfMassPosition();
		cam->setPosition(vector3df(playerPos.x(), playerPos.y()+2.0f, playerPos.z()+mod));

		// stealth movement -> lower the camera a bit and update the player status
		if (inputHandler.isKeyDown(KEY_LCONTROL)) {
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y - .1f, cam->getPosition().Z));
			player->setStealth(true);
		}
		else if (player->isStealthActive()){
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y + .1f, cam->getPosition().Z));
			player->setStealth(false);
		}

		if (player->getNode()->getPosition().Y > bedroom->getNode()->getPosition().Y - bedroom->getNode()->getScale().Y*2) {
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

		// zoom in or out so you can see the player
		if (inputHandler.isKeyDown(KEY_PLUS) && !inputHandler.wasKeyDown(KEY_PLUS)) {
			mod++;
		}
		if (inputHandler.isKeyDown(KEY_MINUS) && !inputHandler.wasKeyDown(KEY_MINUS)) {
			mod--;
		}
		
		// resets the position and velocity of the object object
		/*if (inputHandler.isKeyDown(KEY_KEY_1) && !inputHandler.wasKeyDown(KEY_KEY_1)) {
			//tester->~Object();
			transform = tester->getRigidBody()->getCenterOfMassTransform();
			transform.setOrigin(btVector3(player->getNode()->getPosition().X, player->getNode()->getPosition().Y, player->getNode()->getPosition().Z));
			tester->getRigidBody()->setCenterOfMassTransform(transform);
			tester->getRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		}*/

		// set the camera position so it follows the player
		btVector3 playerPos = player->getRigidBody()->getCenterOfMassPosition();
		cam->setPosition(vector3df(playerPos.x(), playerPos.y()+2.0f, playerPos.z()+mod));

		// stealth movement -> lower the camera a bit and update the player status
		if (inputHandler.isKeyDown(KEY_LCONTROL)) {
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y - .1f, cam->getPosition().Z));
			player->setStealth(true);
		}
		else if (player->isStealthActive()){
			cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y + .1f, cam->getPosition().Z));
			player->setStealth(false);
		}

		if (player->getNode()->getPosition().Y > bedroom->getNode()->getPosition().Y - bedroom->getNode()->getScale().Y*2) {
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

		vector3df pos = player->getNode()->getPosition();
		std::wstringstream sstream;
<<<<<<< HEAD
=======

>>>>>>> eb236c080a83e866b47b64f67903d66407a63396
		sstream << "x:" << pos.X << " y: " << pos.Y << " z: " << pos.Z << ". CI: " << player->getCollectedItems().size();
		text->setText(sstream.str().c_str());

		//render
		if(!game.render()) break;
<<<<<<< HEAD
=======

		if (!player->isAlive()){
			break;
		}
>>>>>>> eb236c080a83e866b47b64f67903d66407a63396

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
	ISceneNode* node = game.getDevice()->getSceneManager()->addCubeSceneNode(1.0f);
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
	ISceneNode* node  = game.getDevice()->getSceneManager()->addSphereSceneNode(radius, 32);

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