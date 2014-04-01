//add Irrlicht
#pragma comment (lib, "Irrlicht")

#include <Irrlicht.h>
#include "Game.h"
#include "TargetCamera.h"
#include "PhysicsEntity.h"
#include "PhysicsEngine.h"
#include "Player.h"
#include "Object.h"
#include "Enemy.h"
#include <IGUIFont.h>
#include "EntityManager.h"
#include <sstream>
#include "Collectable.h"

using namespace irr;
using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;
using namespace GameEngine;

// function header to add a box to our game world
void createBox(const std::string& name, const vector3df& position, const vector3df& scale, float mass);
//function header to add a sphere
void createSphere(const std::string& name, const vector3df& position, float radius, float mass);



int main (){
	Player* player = new Player();

	Object* fish = new Object("fish", vector3df(-15.0f, 0.0f, 5.0f));
	Object* spray = new Object("spray", vector3df(-15.0f, 0.0f, 15.0f));
	Object* carrot = new Object("carrot", vector3df(-15.0f, 0.0f, -15.0f));
	Object* bone = new Object("bone", vector3df(15.0f, 0.0f, -15.0f));
	
	Collectable* socks = new Collectable("socks", vector3df(-10.0f, 0.0f, -10.0f));
	Collectable* jeans = new Collectable("jeans", vector3df(10.0f, 0.0f, 10.0f));
	Collectable* shoes = new Collectable("shoes", vector3df(-10.0f, 0.0f, 10.0f));
	Collectable* shirt = new Collectable("shirt", vector3df(10.0f, 0.0f, -10.0f));


	Enemy* fatcat = new Enemy("fatcat", vector3df(10.0f, 0.0f, 10.0f), 5.0f);
	Enemy* cat = new Enemy("cat", vector3df(-10.0f, 0.0f, -10.0f), 10.0f);
	Enemy* dog = new Enemy("dog", vector3df(-10.0f, 0.0f, 10.0f), 10.0f);
	Enemy* rabbit = new Enemy("rabbit", vector3df(10.0F, 0.0F, -10.0F), 10.0f);

	
	
	//setup window
	game.setCaption(L"State Machines");
	game.setDimensions(dimension2d<u32>(1200,900));

	//add a camera
	TargetCamera* cam = new TargetCamera();
	cam->setPosition(vector3df(0.0f,30.0f,30.0f));
	cam->setTarget(vector3df(0.0f,0.0f,0.0f));
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



	//create a floor
	createBox("Floor", vector3df(0.0f, -5.0f, 0.0f), vector3df(50.0f, 0.5f, 50.0f), 0.0f);

	//create a wall
	createBox("Wall", vector3df(25.0f, 0.0f, 0.0f), vector3df(0.5f, 10.0f, 50.0f), 0.0f);
	createBox("Wall", vector3df(-25.0f, 0.0f, 0.0f), vector3df(0.5f, 10.0f, 50.0f), 0.0f);

	//set up timers
	u32 prevTime = game.getDevice()->getTimer()->getRealTime();
	u32 currTime;
	float deltaTime;

	while(game.getDevice()->run()){
		//update timers
		currTime = game.getDevice()->getTimer()->getRealTime();
		deltaTime = float (currTime - prevTime)/1000.0f;

		//escape!
		if(inputHandler.isKeyDown(KEY_ESCAPE)){
			break;
		}

		//update
		if(!game.update(deltaTime)) break;

		//render
		if(!game.render()) break;

		//random stuff...
		
		
		Player* player = (Player*)EntityManager::getNamedEntities("Player")->front();
		vector3df playerPos = player->getNode()->getPosition();
		std::wstringstream sstream;
		sstream << "x:" << playerPos.X << " y: " << playerPos.Y << " z: " << playerPos.Z << ". CI: "<< player->getCollectedItems().size() ;
		text->setText(sstream.str().c_str());
		//cout <<  << endl;

		prevTime = currTime;
	}

	//game ended unload and shutdown
	game.unloadContent();
	// shutdown game
	game.shutdown();
}


// function to add a box to our game world
void createBox(const std::string& name, const vector3df& position, const vector3df& scale, float mass){
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
	physicsEntity->setRigidBody(PhysicsEngine::createBoxRigidBody(physicsEntity, scale, mass));
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