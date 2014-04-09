/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Collectable.h"
#include "ContentDecision.h"
#include "Decision.h"
#include "DecisionTreeNode.h"
#include "DistanceToGuardedItemDecision.h"
#include "DistanceToPlayerDecision.h"
#include "DistanceToWeaknessDecision.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "FleePlayerDecision.h"
#include "FleeState.h"
#include "FleeWeaknessDecision.h"
#include "Game.h"
#include "MessageHandler.h"
#include "NormalDecision.h"
#include "Object.h"
#include "PhysicsEntity.h"
#include "Player.h"
#include "PlayerInRoomDecision.h"
#include "Seek.h"
#include "SeekGuardedItemDecision.h"
#include "SeekPlayerDecision.h"
#include "SeekState.h"
#include "SeekWeaknessDecision.h"
#include "StateNormal.h"
#include "WeaknessInRoomDecision.h"
#include <iostream>
#include <sstream>


using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an Enemy object. Initialises Entity and SM
Enemy::Enemy(std::string name, Room* room, vector3df startPos, float pVel, Object* weakness, Collectable* guardedItem) : Entity(-1, 0, "Enemy"), _stateMachine(this){
	_enemyName = name;
	_velMod = pVel;
	_startPos = room->getPosition()+startPos;
	_guardedItem = guardedItem;
	_weakness = weakness;
	_room = room;
}

//Initialise the enemy and add states to SM
void Enemy::initialise(){
	// find player pointer
	Entity* player = EntityManager::getNamedEntities("Player")->front();

	//Add states to SM
	_stateMachine.addState("Normal", new StateNormal());
	_stateMachine.addState("SeekPlayer", new SeekState(this, player, _velMod));
	_stateMachine.addState("FleePlayer", new FleeState(this, player, _velMod));
	_stateMachine.addState("FleeWeakness", new FleeState(this, this->getWeakness(), _velMod));
	_stateMachine.addState("SeekWeakness", new SeekState(this, this->getWeakness(), _velMod));
	_stateMachine.addState("SeekGuardedItem", new SeekState(this, this->getGuardedItem(), _velMod));

	//set initial state to normal
	_stateMachine.setState("Normal");
	_currentState = "Normal";
	// Set elapsed time to 0
	_elapsedTimeAI = 0.0f;
	_elapsedTimeSound = 1.0f;
	// Create decision tree
	_decisionTree = this->getDecTree(_enemyName);
}

//Load content for the enemy
void Enemy::loadContent(){

	//find mesh
	IAnimatedMesh* mesh = 0;
	std::wstringstream path;
	path << "meshes/" << _enemyName.c_str() << "/" << _enemyName.c_str() << ".obj";
	mesh = game.getDevice()->getSceneManager()->getMesh(path.str().c_str());
	if (!mesh){
		std::cout << "Could not load " << _enemyName.c_str() << " mesh" << std::endl;
		return;
	}

	_node = game.getDevice()->getSceneManager()->addAnimatedMeshSceneNode(mesh);

	//Set Positions and lighting
	_node->setPosition(_startPos);
	_node->setMaterialFlag(EMF_LIGHTING, false);

	//set scales
	if (_enemyName == "fatcat"){
		_node->setScale(vector3df(2, 1, 1));
	}
	else if (_enemyName == "dog") {
		_node->setScale(vector3df(1.5f, 1.5f, 1.5f));
	}
	else {
		_node->setScale(vector3df(1, 1, 1));
	}
	
	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(2.0f, 0.5f, 2.0f), 100);
	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Enemy");
	physicsEntity->setRigidBody(_rigidBody);
}

//updates the enemy
void Enemy::update(float deltaTime){
	// Add elapsed time
	_elapsedTimeAI += deltaTime;
	_elapsedTimeSound += deltaTime;
	Player* player = (Player*)EntityManager::getNamedEntities("Player")->front();

	//AI runs every 1/10th second while player in room, otherwise once per sec.
	float freq = (player->getCurrentRoom() == getRoom()->getName()) ? 0.1 : 1.0;
	if (_elapsedTimeAI > freq)
	{
		// Make decision
		_decisionTree->makeDecision(this);
		// Execute state
		_stateMachine.update(deltaTime);
		//increase noise made if agrod
		if (_currentState == "SeekPlayer"){
			player->decreaseNoiseAllowanceBy(deltaTime * 10);
		}

		// Reset elapsed time
		_elapsedTimeAI = 0.0f;
	}

	/*SOUND STUFF*/
	//fatcat is never agrod is the player in teh same room?
	bool fc = false;
	if (_enemyName == "fatcat"){
		fc = (_currentState == "Normal" && player->getCurrentRoom() == this->getRoom()->getName());
	}

	//play agrod audio if required
	if (_elapsedTimeSound > 1.294 && (_currentState == "SeekPlayer" || fc)){
		std::string path = "sounds/" + _enemyName + "/" + _enemyName + "_agro.wav";
		game.getAudioEngine()->play2D(path.c_str());
		_elapsedTimeSound = 0.0f;

	}

	//if cat, play scared audio if required
	if (_elapsedTimeSound > 1.294 && _enemyName == "cat" && _currentState == "FleeWeakness"){

		std::string path = "sounds/" + _enemyName + "/" + _enemyName + "_scared.wav";
		game.getAudioEngine()->play2D(path.c_str());
		_elapsedTimeSound = 0.0f;
	}

	//play dog eager audio if required
	if (_elapsedTimeSound > 1.294 && _enemyName == "dog" && _currentState == "SeekWeakness"){
		std::string path = "sounds/" + _enemyName + "/" + _enemyName + "_eager.wav";
		game.getAudioEngine()->play2D(path.c_str());
		_elapsedTimeSound = 0.0f;
	}
}


DecisionTreeNode<Enemy>* Enemy::getDecTree(std::string name){
	DecisionTreeNode<Enemy>* result = 0;

	if (name == "fatcat"){// lazy, not afraid of spray - only chases fish
		result =
			new PlayerInRoomDecision(
			new WeaknessInRoomDecision(
			new DistanceToWeaknessDecision(
			10.0f,
			new DistanceToWeaknessDecision(
			2.0f,
			new ContentDecision(),
			new SeekWeaknessDecision()
			),
			new NormalDecision()
			),
			new NormalDecision()
			),
			new NormalDecision()
			);

	}

	if (name == "dog"){// will persue player unless bone is near then will chase bone
		result =
			new PlayerInRoomDecision(
			new WeaknessInRoomDecision(
			new DistanceToWeaknessDecision(
			3.0f,
			new ContentDecision(),
			new SeekWeaknessDecision()
			),

			new SeekPlayerDecision()
			),
			new DistanceToGuardedItemDecision(
			2.0f,
			new NormalDecision(),
			new SeekGuardedItemDecision()
			)
			);
	}

	if (name == "rabbit"){// will lunge at the player at alarming speed if the player doesn't have the holy handgr... ahem, carrot
		result =
			new PlayerInRoomDecision(
			new WeaknessInRoomDecision(
			new DistanceToWeaknessDecision(
			3.0f,
			new ContentDecision(),
			new DistanceToWeaknessDecision(
			15.0f,
			new SeekWeaknessDecision(),
			new NormalDecision()
			)
			),

			new DistanceToPlayerDecision(
			10.0f,
			new SeekPlayerDecision(),
			new NormalDecision()
			)
			),
			new DistanceToGuardedItemDecision(
			4.0f,
			new NormalDecision(),
			new SeekGuardedItemDecision()
			)
			);
	}

	if (name == "cat"){// will watch over socks, moving towards player then back to socks. Will Avoid spray at all costs...
		result = new PlayerInRoomDecision(

			new DistanceToWeaknessDecision(
			2.0f,
			new FleeWeaknessDecision(),
			new DistanceToGuardedItemDecision(
			3.0f,
			new SeekPlayerDecision(),
			new SeekGuardedItemDecision()
			)
			),
			new NormalDecision()
			);
	}

	return result;
}
void Enemy::handleMessage(const Message& message){
	if (message.message == "COLLISION"){
		if (((Entity*)message.data)->getName() == "Player"){
			Player* player = (Player*)message.data;
			if (player->getCarriedItem() != _weakness && (_currentState == "SeekPlayer" || _currentState == "Normal" || _currentState == "SeekGuardedItem")){
				Message m(player, "Die", this);
				MessageHandler::sendMessage(m);
			}
		}
	}
}
