//add Irrlicht
#pragma comment (lib, "Irrlicht")
//add IrrKlang
#pragma comment (lib, "irrKlang.lib")

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

const float WALL_THIKNESS = 0.5f;
const float WALL_HEIGHT = 7.5f;
const float ROOM_SIZE = 20.0f;
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;


void createHouse() {
	Room* bedroom = new Room("Bedroom", "textures/wall_rose_paint.jpg", "textures/bedroom-carpet.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{2,3}, 2);
	Room* hall = new Room("Hall", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2, 3, 4}, 0);
	Room* bathroom = new Room("Bathroom", "textures/wall_rose_paint.jpg", "textures/bathroom-floor.jpg", "textures/ceiling.jpg", vector3df(ROOM_SIZE, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{2}, 0);
	Room* studyroom = new Room("Studyroom", "textures/wall_rose_paint.jpg", "textures/study-carpet.jpg", "textures/ceiling.jpg", vector3df(-ROOM_SIZE, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1}, 0);
	Room* livingroom = new Room("Livingroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 2*ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2, 4}, 0);
	Room* kitchen = new Room("Kitchen", "textures/wall_rose_paint.jpg", "textures/18_FLOOR TEXTURE _2.jpg", "textures/ceiling.jpg", vector3df(ROOM_SIZE, 0.0f, 2*ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{2}, 0);
	Room* hallexit = new Room("Hallexit", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(-ROOM_SIZE, 0.0f, 2*ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2}, 2);

	// BEDROOM
	Furniture* girl = bedroom->addObject("girl", bedroom->getName(), "girl_3.obj", vector3df(0, WALL_HEIGHT / 3.5f, ROOM_SIZE / 3.5f), vector3df(1.45f, 1.45f, 1.45f), 0.0f);
	girl->setRotationAngle(-PI / 2);
	girl->setRotationAxis(new btVector3(1, 0, 0));
	Furniture* bed = bedroom->addObject("bed", bedroom->getName(), "bed.obj", vector3df(0, WALL_HEIGHT / 2.3f, ROOM_SIZE / 3), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomDresser = bedroom->addObject("cabinet", bedroom->getName(), "dresser.obj", vector3df(ROOM_SIZE/7, WALL_HEIGHT / 2.3f, ROOM_SIZE / 2 - WALL_THIKNESS*2), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomChest = bedroom->addObject("cabinet", bedroom->getName(), "chest.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS*2, WALL_HEIGHT / 2.3f, ROOM_SIZE / 5), vector3df(.02f, .02f, .02f), 0.0f);
	bedroomChest->setRotationAngle(-PI / 2);
	bedroomChest->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* bedroomBookcase = bedroom->addObject("cabinet", bedroom->getName(), "chest.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, WALL_HEIGHT / 2.3f, ROOM_SIZE / 5), vector3df(.02f, .02f, .02f), 0.0f);







	Furniture* bedroomWindow1 = bedroom->addObject("window", bedroom->getName(), "window.obj", vector3df(0.0f, WALL_HEIGHT / 3, ROOM_SIZE / 2 - WALL_THIKNESS/2), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomWindow2 = bedroom->addObject("window", bedroom->getName(), "window.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS / 2, WALL_HEIGHT / 3, 0.0f), vector3df(.02f, .02f, .02f), 0.0f);
	bedroomWindow2->setRotationAngle(-PI / 2);
	bedroomWindow2->setRotationAxis(new btVector3(0, 1, 0));

	//Furniture* aquarium = bedroom->addObject("bone", bedroom->getName(), "FEMUR.3ds", vector3df(-5.0f, WALL_HEIGHT / 2, 5.0f), vector3df(.02f, .02f, .02f), .0f);
	//Furniture* fish = bedroom->addObject("fish", bedroom->getName(), "Golden_Fish_OBJ.obj", vector3df(-5.0f, WALL_HEIGHT / 3.7f, 5.0f), vector3df(.01f, .01f, .03f), 0.0f);

	// ADDING STUFF

	Object* fish = new Object("fish", vector3df(0.0f, 0.0f, 0.0f));//leave there
	Object* spray = new Object("spray", vector3df(-15.0f, 0.0f, 15.0f));//leave there
	Object* carrot = new Object("carrot", vector3df(15.0f, 0.0f, 10.0f));//t
	Object* bone = new Object("bone", vector3df(0.0f, 0.0f, 15.0f));//t

	Collectable* socks = new Collectable("socks", vector3df(-5.5f, 0.0f, 35.5f));
	Collectable* jeans = new Collectable("jeans", vector3df(-20.0f, 0.0f, 24.5f));
	Collectable* shoes = new Collectable("shoes", vector3df(-20.0f, 0.0f, 20.0f));
	Collectable* shirt = new Collectable("shirt", vector3df(20.5f, 0.0f, 9.25f));

	Enemy* fatcat = new Enemy("fatcat", kitchen, vector3df(26.0f, 0.0f, 46.0f), 5.0f, fish, shirt);
	Enemy* cat = new Enemy("cat", livingroom, vector3df(5.0f, 0.0f, 43.0f), 5.0f, spray, socks);
	Enemy* dog = new Enemy("dog", studyroom, vector3df(-18.0f, 0.0f, 18.0f), 5.0f, bone, shoes);
	Enemy* rabbit = new Enemy("rabbit", hallexit, vector3df(-26.0, 0.0f, 42.0f), 20.0f, carrot, jeans);
}

int main (){
	Player* player = new Player();

	createHouse();


	//setup window
	game.setCaption(L"State Machines");
	game.setDimensions(dimension2d<u32>(SCREEN_WIDTH, SCREEN_HEIGHT));

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

	game.getAudioEngine()->play2D("sounds/common/background.wav", true);

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
	irr::gui::ICursorControl* cursor = game.getDevice()->getCursorControl();
	cursor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	cursor->setVisible(false);
	vector2di prevCursorPos = vector2di(cursor->getPosition().X, cursor->getPosition().Y);
	int mouseMovementX = 0;
	int mouseMovementY = 0;
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

		if (player->getRigidBody()->getCenterOfMassPosition().y() - player->getNode()->getScale().Y > -WALL_HEIGHT/2+WALL_THIKNESS*2) {
			player->setDown(false);
		}
		else
			player->setDown(true);

		/* MOUSE MOVEMENT */
		// Now check if the mouse has moved

		// reset the cursor if goes offscreen an update the previous position
		if (cursor->getPosition().X >= SCREEN_WIDTH || cursor->getPosition().X <= 0) {
			cursor->setPosition(SCREEN_WIDTH/2, cursor->getPosition().Y);
			prevCursorPos.X = cursor->getPosition().X;
		}
		if (cursor->getPosition().Y >= SCREEN_HEIGHT || cursor->getPosition().Y <= 0) {
			cursor->setPosition(cursor->getPosition().X, SCREEN_HEIGHT / 2);
			prevCursorPos.Y = cursor->getPosition().Y;
		}

		mouseMovementX = cursor->getPosition().X - prevCursorPos.X;
		mouseMovementY = cursor->getPosition().Y - prevCursorPos.Y;

		// Rotate the camera and player by the change in the mouse position. 
		player->rotate(mouseMovementX * deltaTime, mouseMovementY * deltaTime);
		cam->rotate(mouseMovementX * deltaTime, mouseMovementY * deltaTime);

		// update previous mouse position
		prevCursorPos = vector2di(cursor->getPosition().X, cursor->getPosition().Y);

		//update
		if(!game.update(deltaTime)) break;

		vector3df pos = player->getNode()->getPosition();
		std::wstringstream sstream;
		sstream << "x:" << pos.X << " y: " << pos.Y << " z: " << pos.Z << "\nCI: " << player->getCollectedItems().size() << "; NM: " << player->getNoiseMade();
		text->setText(sstream.str().c_str());

		//render
		if(!game.render()) break;

		prevTime = currTime;
	}

	//game ended unload and shutdown
	game.unloadContent();
	// shutdown game
	game.shutdown();
}