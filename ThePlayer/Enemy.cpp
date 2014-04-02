#include "Enemy.h"
#include "Player.h"
#include "MessageHandler.h"
#include "StateNormal.h"
#include "StateSpin.h"
#include "Game.h"
#include "EntityManager.h"
#include "DecisionTreeNode.h"
#include "Spin2.h"
#include "Decision.h"
#include "NormalDecision.h"
#include "Spin2Decision.h"
#include "SpinDecision.h"
#include "DistanceToPlayerDecision.h"
#include "RandomDecision.h"
#include "SeekState.h"
#include "Seek.h"
#include "SeekPlayerDecision.h"
#include "SeekGuardedItemDecision.h"
#include "FleeState.h"
#include "FleePlayerDecision.h"
#include "FleeWeaknessDecision.h"
#include "SeekWeaknessDecision.h"
#include "Object.h"
#include <iostream>
#include "Collectable.h"
#include <sstream>
#include "PhysicsEntity.h"
#include "DistanceToGuardedItemDecision.h"
#include "DistanceToWeaknessDecision.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an Enemy object. Initialises Entity and SM
Enemy::Enemy(std::string name, vector3df startPos, float pVel, Object* weakness, Collectable* guardedItem) : Entity(-1, 0, "Enemy"), _stateMachine(this){
	_enemyName = name;
	_velMod = pVel;
	_startPos = startPos;
	_guardedItem = guardedItem;
	_weakness = weakness;
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
	// Set elapsed time to 0
	_elapsedTime = 0.0f;
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
		_node->setScale(vector3df(1.5f, 1, 1));
	}
	else if (_enemyName == "cat"){
		_node->setScale(vector3df(1.0f, 1.0f, 1.0f));
	}
	else if (_enemyName == "rabbit") {
		_node->setScale(vector3df(1, 1, 1));
	}
	else if (_enemyName == "dog") {
		_node->setScale(vector3df(1.5f, 1.5f, 1.5f));
	}

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(0.5f, 0.5f, 0.5f), 100);
	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Enemy");
	physicsEntity->setRigidBody(_rigidBody);

}

//updates the enemy
void Enemy::update(float deltaTime){
	// Add elapsed time
	_elapsedTime += deltaTime;

	// Run AI every half second

	float freq = 0.1f;
	if (_elapsedTime > freq)
	{
		// Make decision
		_decisionTree->makeDecision(this);
		// Execute state
		_stateMachine.update(deltaTime);
		// Reset elapsed time
		_elapsedTime = 0.0f;
	}
}


DecisionTreeNode<Enemy>* Enemy::getDecTree(std::string name){
	DecisionTreeNode<Enemy>* result = 0;

	if (name == "fatcat"){
		result = new DistanceToPlayerDecision(
			30.0f,
			new DistanceToWeaknessDecision(
			10.0f,
			new DistanceToWeaknessDecision(
			2.0f,
			new NormalDecision(),
			new SeekWeaknessDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "dog"){
		result = new DistanceToPlayerDecision(
			30.0f,
			new DistanceToWeaknessDecision(
			10.0f,
			new DistanceToWeaknessDecision(
			2.0f,
			new NormalDecision(),
			new SeekWeaknessDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "rabbit"){
		result = new DistanceToPlayerDecision(
			30.0f,
			new DistanceToWeaknessDecision(
			10.0f,
			new DistanceToWeaknessDecision(
			2.0f,
			new NormalDecision(),
			new SeekWeaknessDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "cat"){// will watch over socks, moving towards player then back to socks. Will Avoid spray at all costs...
		result = new DistanceToPlayerDecision(
			10.0f,
			new DistanceToWeaknessDecision(
			4.0f,
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

			//send message to player that item has been picked up
			Message m(player, "Die", this);
			MessageHandler::sendMessage(m);
		}
	}
}
