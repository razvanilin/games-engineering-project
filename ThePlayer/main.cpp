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
#include "Menu.h"
#include "HudManager.h"
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

Furniture* sign = 0;

void createHouse() {
	Room* bedroom = new Room("Bedroom", "textures/wall_rose_paint.jpg", "textures/bedroom-carpet.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 0.0f), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{3}, 0);
	Room* hall = new Room("Hall", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2, 3, 4}, 0);
	Room* bathroom = new Room("Bathroom", "textures/wall_rose_paint.jpg", "textures/bathroom-floor.jpg", "textures/ceiling.jpg", vector3df(ROOM_SIZE, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{2}, 0);
	Room* studyroom = new Room("Studyroom", "textures/wall_rose_paint.jpg", "textures/study-carpet.jpg", "textures/ceiling.jpg", vector3df(-ROOM_SIZE, 0.0f, ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1}, 0);
	Room* livingroom = new Room("Livingroom", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(0.0f, 0.0f, 2 * ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2, 4}, 0);
	Room* kitchen = new Room("Kitchen", "textures/wall_rose_paint.jpg", "textures/18_FLOOR TEXTURE _2.jpg", "textures/ceiling.jpg", vector3df(ROOM_SIZE, 0.0f, 2 * ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{2}, 0);
	Room* hallexit = new Room("Hallexit", "textures/wall_rose_paint.jpg", "textures/wood.jpg", "textures/ceiling.jpg", vector3df(-ROOM_SIZE, 0.0f, 2 * ROOM_SIZE), vector3df(WALL_THIKNESS, WALL_HEIGHT, ROOM_SIZE), new int[]{1, 2}, 2);

	/**** BEDROOM ****/
	Furniture* girl = bedroom->addFurniture("girl", bedroom->getName(), "girl_3.obj", vector3df(0, -WALL_HEIGHT / 3.5f, -ROOM_SIZE / 3.5f), vector3df(1.45f, 1.45f, 1.45f), 0.0f);
	girl->setRotationAngle(-PI / 2);
	girl->setRotationAxis(new btVector3(1, 0, 0));

	Furniture* bed = bedroom->addFurniture("bed", bedroom->getName(), "bed.obj", vector3df(0, -WALL_HEIGHT / 2.3f, -ROOM_SIZE / 3), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomDresser = bedroom->addFurniture("cabinet", bedroom->getName(), "dresser.obj", vector3df(-ROOM_SIZE / 7, -WALL_HEIGHT / 2.3f, -ROOM_SIZE / 2 + WALL_THIKNESS * 2), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomChest = bedroom->addFurniture("cabinet", bedroom->getName(), "chest.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, -WALL_HEIGHT / 2.3f, -ROOM_SIZE / 5), vector3df(.02f, .02f, .02f), 0.0f);
	bedroomChest->setRotationAngle(-PI / 2);
	bedroomChest->setRotationAxis(new btVector3(0, 1, 0));

	Furniture* bedroomBookcase = bedroom->addFurniture("bookcase", bedroom->getName(), "bookcase2.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.2f, 0.0f), vector3df(.02f, .02f, .02f), 0.0f);
	bedroomBookcase->setRotationAngle(PI / 2);
	bedroomBookcase->setRotationAxis(new btVector3(0, 1, 0));

	Furniture* bedroomWindow1 = bedroom->addFurniture("window", bedroom->getName(), "window.obj", vector3df(0.0f, -WALL_HEIGHT / 3, -ROOM_SIZE / 2 + WALL_THIKNESS / 2), vector3df(.02f, .02f, .02f), 0.0f);
	Furniture* bedroomWindow2 = bedroom->addFurniture("window", bedroom->getName(), "window.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS / 2, -WALL_HEIGHT / 3, 0.0f), vector3df(.02f, .02f, .02f), 0.0f);
	bedroomWindow2->setRotationAngle(-PI / 2);
	bedroomWindow2->setRotationAxis(new btVector3(0, 1, 0));

	/**** HALL ****/
	Furniture* carrotPlant = hall->addFurniture("plant", hall->getName(), "plant.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 3), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	Furniture* hallCabinet = hall->addFurniture("cabinet", hall->getName(), "glasscabinet.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 4), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	hallCabinet->setRotationAngle(PI / 2);
	hallCabinet->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* hallCouch = hall->addFurniture("couch", hall->getName(), "Couch.obj", vector3df(-ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 3, -ROOM_SIZE / 2 + WALL_THIKNESS * 3), vector3df(1.0f, 1.0f, 1.0f), 0.0f);
	Furniture* hallTable = hall->addFurniture("table", hall->getName(), "coffeetable.obj", vector3df(-ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 3), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	Furniture* hallShelves = hall->addFurniture("bookcase", hall->getName(), "bookcase.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 3), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	hallShelves->setRotationAngle(-PI / 2);
	hallShelves->setRotationAxis(new btVector3(0, 1, 0));

	/**** STUDYROOM ****/
	Furniture* studyDesk = studyroom->addFurniture("desk", hall->getName(), "computerdesk.obj", vector3df(0.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 3), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	studyDesk->setRotationAngle(-PI / 2);
	studyDesk->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* studyShelves = studyroom->addFurniture("bookcase", hall->getName(), "bookcase.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 3), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	studyShelves->setRotationAngle(-PI / 2);
	studyShelves->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* studyBookcase = studyroom->addFurniture("bookcase", hall->getName(), "bookcase2.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, 0.0f), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	studyBookcase->setRotationAngle(PI / 2);
	studyBookcase->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* studyPiano = studyroom->addFurniture("misc", hall->getName(), "piano.obj", vector3df(ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	studyPiano->setRotationAngle(PI);
	studyPiano->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* studyStool = studyroom->addFurniture("chair", hall->getName(), "stool.obj", vector3df(ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2.5f), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	Furniture* studyPlant = studyroom->addFurniture("plant", hall->getName(), "plant.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 2.0f + WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);

	/**** BATHROOM ****/

	Furniture* toilet = bathroom->addFurniture("toilet", bathroom->getName(), "toilet.obj", vector3df(-ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 2.0f + WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	Furniture* bath = bathroom->addFurniture("bath", bathroom->getName(), "bath.obj", vector3df(ROOM_SIZE / 2.5f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, 0.0f), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	bath->setRotationAngle(PI / 2);
	bath->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* washbasin = bathroom->addFurniture("bath", bathroom->getName(), "washbasin.obj", vector3df(0.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2.0f - WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);

	/**** LIVINGROOM ****/

	Furniture* aquarium = livingroom->addFurniture("aquarium", livingroom->getName(), "aquarium.obj", vector3df(-ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 2 + WALL_THIKNESS * 2), vector3df(.02f, .02f, .02f), .0f);
	Furniture* tv = livingroom->addFurniture("misc", livingroom->getName(), "tv.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 2), vector3df(.02f, .02f, .02f), .0f);
	tv->setRotationAngle(2.35f);
	tv->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* couchLivingroom = livingroom->addFurniture("couch", livingroom->getName(), "Couch.obj", vector3df(-ROOM_SIZE / 5, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 5), vector3df(1.0f, 1.0f, 1.0f), .0f);
	couchLivingroom->setRotationAngle(-PI / 4);
	couchLivingroom->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* livingroomShelves = livingroom->addFurniture("bookcase", livingroom->getName(), "bookcase.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 3), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	livingroomShelves->setRotationAngle(-PI / 2);
	livingroomShelves->setRotationAxis(new btVector3(0, 1, 0));

	Furniture* test0 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100,100,100), vector3df(.02f, .02f, .02f), .0f);
	Furniture* test1 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100, 100, 100), vector3df(.02f, .02f, .02f), .0f);
	Furniture* test2 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100, 100, 100), vector3df(.02f, .02f, .02f), .0f);
	Furniture* test3 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100, 100, 100), vector3df(.02f, .02f, .02f), .0f);
	Furniture* test4 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100, 100, 100), vector3df(.02f, .02f, .02f), .0f);
	Furniture* test5 = bedroom->addFurniture("plant", bedroom->getName(), "plant.obj", vector3df(100, 100, 100), vector3df(.02f, .02f, .02f), .0f);

	/**** KITCHEN ****/
	Furniture* trash = kitchen->addFurniture("kitchen", kitchen->getName(), "trash.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 2), vector3df(0.01f,0.01f,0.01f), 0.0f);
	Furniture* fridge = kitchen->addFurniture("kitchen", kitchen->getName(), "fridge.obj", vector3df(0.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 2 + WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	Furniture* washingmachine = kitchen->addFurniture("kitchen", kitchen->getName(), "washingmachine.obj", vector3df(2.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE / 2 + WALL_THIKNESS * 2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	Furniture* cooker = kitchen->addFurniture("kitchen", kitchen->getName(), "cooker.obj", vector3df(0.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 3), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	cooker->setRotationAngle(PI);
	cooker->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* kitchenCabinet1 = kitchen->addFurniture("kitchen", kitchen->getName(), "cabinet.obj", vector3df(1.5f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 3), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	kitchenCabinet1->setRotationAngle(PI);
	kitchenCabinet1->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* kitchenCabinet2 = kitchen->addFurniture("kitchen", kitchen->getName(), "cabinet.obj", vector3df(-2.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2 - WALL_THIKNESS * 3), vector3df(0.03f, 0.03f, 0.03f), 0.0f);
	kitchenCabinet2->setRotationAngle(PI);
	kitchenCabinet2->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* kitchenTable = kitchen->addFurniture("table", kitchen->getName(), "rectangulartable.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, 0.0f), vector3df(0.025f, 0.025f, 0.025f), 0.0f);
	kitchenTable->setRotationAngle(PI / 2);
	kitchenTable->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* kitchenChair1 = kitchen->addFurniture("chair", kitchen->getName(), "chair.obj", vector3df(ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, 1.0f), vector3df(0.025f, 0.025f, 0.025f), 0.0f);
	kitchenChair1->setRotationAngle(PI / 2);
	kitchenChair1->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* kitchenChair2 = kitchen->addFurniture("chair", kitchen->getName(), "chair.obj", vector3df(ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -1.0f), vector3df(0.025f, 0.025f, 0.025f), 0.0f);
	kitchenChair2->setRotationAngle(PI / 2);
	kitchenChair2->setRotationAxis(new btVector3(0, 1, 0));

	/**** EXIT ****/
	Furniture* rack = hallexit->addFurniture("rack", hallexit->getName(), "Clothes Rack.3DS", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -4.0f), vector3df(0.02f, 0.02f, 0.02f), 0.0f);
	sign = hallexit->addFurniture("sign", hallexit->getName(), "schild OBJ.obj", vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, 4.0f), vector3df(0.003f, 0.005f, 0.003f), 0.0f);
	sign->setRotationAngle(PI/2);
	sign->setRotationAxis(new btVector3(0, 1, 0));
	Furniture* exitPlant = hallexit->addFurniture("plant", hallexit->getName(), "plant.obj", vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE/2 + WALL_THIKNESS*2), vector3df(0.03f, 0.03f, 0.03f), 0.0f);


	// ADDING STUFF

	Object* fish = new Object("fish", "fish.obj", vector3df(0.0f, 0.0f, 0.0f));
	fish->setScale(vector3df(0.01f, 0.01f, 0.02f));
	livingroom->placeObject(fish, vector3df(-ROOM_SIZE / 3, -WALL_HEIGHT / 4.5f, -ROOM_SIZE / 2 + WALL_THIKNESS * 2));
	Object* spray = new Object("spray", "spray.3ds", vector3df(-15.0f, 0.0f, 15.0f));
	spray->setScale(vector3df(0.003f, 0.003f, 0.003f));
	hallexit->placeObject(spray, vector3df(ROOM_SIZE / 3, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, -ROOM_SIZE/2 + WALL_THIKNESS*2));
	Object* carrot = new Object("carrot", "carrot.3ds", vector3df(15.0f, 0.0f, 10.0f));
	carrot->setScale(vector3df(0.005f, 0.005f, 0.005f));
	hall->placeObject(carrot, vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 3.5f, -WALL_HEIGHT / 2.2f, ROOM_SIZE / 2 - WALL_THIKNESS * 3));
	Object* bone = new Object("bone", "FEMUR.3ds", vector3df(0.0f, 0.0f, 15.0f));
	bone->setScale(vector3df(0.0015f, 0.0015f, 0.0015f));
	kitchen->placeObject(bone, vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, -WALL_HEIGHT / 3.0f, ROOM_SIZE / 2 - WALL_THIKNESS * 2));
	Object* key = new Object("key", "Key_B_02.3ds", vector3df(0, 0, 0));
	key->setScale(vector3df(0.05f, 0.05f, 0.05f));
	studyroom->placeObject(key, vector3df(0.0f, -WALL_HEIGHT / 4.0f, ROOM_SIZE / 2 - WALL_THIKNESS * 3));

	Collectable* socks = new Collectable("socks", vector3df(-5.5f, 0.0f, 35.5f));
	Collectable* jeans = new Collectable("jeans", vector3df(-20.0f, 0.0f, 24.5f));
	Collectable* shoes = new Collectable("shoes", vector3df(-20.0f, 0.0f, 20.0f));
	Collectable* shirt = new Collectable("shirt", vector3df(20.5f, 0.0f, 9.25f));
	Collectable* wallet = new Collectable("wallet", vector3df(0.0f, 0.0f, 0.0f));
	Collectable* pills = new Collectable("pill-bottle", vector3df(0, 0, 0));
	bedroom->placeCollectable(wallet, vector3df(ROOM_SIZE / 2 - WALL_THIKNESS * 2, 0, -ROOM_SIZE / 3));
	studyroom->placeCollectable(shoes, vector3df(-ROOM_SIZE/2 + WALL_THIKNESS*2, 0.0f, ROOM_SIZE/2 - WALL_THIKNESS*2));
	bathroom->placeCollectable(pills, vector3df(1.0f, -WALL_HEIGHT / 2.0f + WALL_THIKNESS / 2, ROOM_SIZE / 2.0f - WALL_THIKNESS * 2));
	livingroom->placeCollectable(socks, vector3df(0 , 0, ROOM_SIZE/2 - WALL_THIKNESS*2));
	kitchen->placeCollectable(shirt, vector3df(ROOM_SIZE/2 - WALL_THIKNESS*2, 0, -ROOM_SIZE/2 + WALL_THIKNESS*2));
	hallexit->placeCollectable(jeans, vector3df(-ROOM_SIZE / 2 + WALL_THIKNESS * 2, 0, ROOM_SIZE / 2 - WALL_THIKNESS * 2));

	Enemy* fatcat = new Enemy("fatcat", kitchen, vector3df(ROOM_SIZE / 2.5f, -WALL_HEIGHT/3, -ROOM_SIZE / 2.5f), 5.0f, fish, shirt);
	Enemy* cat = new Enemy("cat", livingroom, vector3df(0.0f, -WALL_HEIGHT/3, ROOM_SIZE/3), 5.0f, spray, socks);
	Enemy* dog = new Enemy("dog", studyroom, vector3df(-ROOM_SIZE / 3, WALL_HEIGHT/3, ROOM_SIZE / 3), 5.0f, bone, shoes);
	Enemy* rabbit = new Enemy("rabbit", hallexit, vector3df(-ROOM_SIZE/3.5f, -WALL_HEIGHT/3, ROOM_SIZE/3.5f), 20.0f, carrot, jeans);
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

	HudManager* hudMan = new HudManager();
	//Menu* menu = new Menu();
	sign->getNode()->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg"));

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
	irr::gui::ICursorControl* cursor = game.getDevice()->getCursorControl();
	cursor->setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	cursor->setVisible(false);
	vector2di prevCursorPos = vector2di(cursor->getPosition().X, cursor->getPosition().Y);
	int mouseMovementX = 0;
	int mouseMovementY = 0;
	bool gamePaused = false;
	
	while (game.getDevice()->run()){
		//update timers
		currTime = game.getDevice()->getTimer()->getRealTime();
		deltaTime = float(currTime - prevTime) / 1000.0f;

		//escape!
		if (inputHandler.isKeyDown(KEY_ESCAPE)){
			break;
		}
		if (!gamePaused) {
			// zoom in or out so you can see the player
			if (inputHandler.isKeyDown(KEY_PLUS) && !inputHandler.wasKeyDown(KEY_PLUS)) {
				mod++;
			}
			if (inputHandler.isKeyDown(KEY_MINUS) && !inputHandler.wasKeyDown(KEY_MINUS)) {
				mod--;
			}

			// set the camera position so it follows the player
			btVector3 playerPos = player->getRigidBody()->getCenterOfMassPosition();
			cam->setPosition(vector3df(playerPos.x(), playerPos.y() + 2.0f, playerPos.z() + mod));

			// stealth movement -> lower the camera a bit and update the player status
			if (inputHandler.isKeyDown(KEY_LCONTROL)) {
				cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y - .1f, cam->getPosition().Z));
				player->setStealth(true);
			}
			else if (player->isStealthActive()){
				cam->setPosition(vector3df(cam->getPosition().X, cam->getPosition().Y + .1f, cam->getPosition().Z));
				player->setStealth(false);
			}

			if (player->getRigidBody()->getCenterOfMassPosition().y() - player->getNode()->getScale().Y > -WALL_HEIGHT / 2 + WALL_THIKNESS * 2) {
				player->setDown(false);
			}
			else
				player->setDown(true);

			/* MOUSE MOVEMENT */
			// Now check if the mouse has moved

			// reset the cursor if goes offscreen an update the previous position
			if (cursor->getPosition().X >= SCREEN_WIDTH || cursor->getPosition().X <= 0) {
				cursor->setPosition(SCREEN_WIDTH / 2, cursor->getPosition().Y);
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

			
		}

		//Pause the game
		if (inputHandler.isKeyDown(KEY_KEY_P) && !inputHandler.wasKeyDown(KEY_KEY_P)) {
			if (gamePaused) {
				gamePaused = false;
				prevCursorPos = cursor->getPosition();
			}
			else {
				gamePaused = true;
			}
			cursor->setVisible(gamePaused);
		}
		if (gamePaused) deltaTime = 0;
		//update
		if (!game.update(deltaTime)) break;
		/*vector3df pos = player->getNode()->getPosition();
		std::wstringstream sstream;
		sstream << "x:" << pos.X << " y: " << pos.Y << " z: " << pos.Z << "\nCI: " << player->getCollectedItems().size() << "; NM: " << player->getNoiseMade();
		text->setText(sstream.str().c_str());*/

		//render
		if (!gamePaused) {
			if (!game.render()) break;
			ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg");
			IGUIImage* img = guienv->addImage(texture, position2d<s32>(game.getDimensions().Width, game.getDimensions().Height), false);
		}
		else {
			ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg");
			IGUIImage* img = guienv->addImage(texture, position2d<s32>(game.getDimensions().Width, game.getDimensions().Height), false);
			//img->setUseAlphaChannel(1);
		}

		prevTime = currTime;
	}

	//game ended unload and shutdown
	game.unloadContent();
	// shutdown game
	game.shutdown();
}