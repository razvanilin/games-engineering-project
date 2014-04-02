#include "Enemy.h"
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
#include "DistanceToSprayDecision.h"
#include "DistanceToFishDecision.h"
#include "DistanceToSocksDecision.h"
#include "DistanceToBoneDecision.h"
#include "DistanceToCarrotDecision.h"
#include "RandomDecision.h"
#include "SeekState.h"
#include "Seek.h"
#include "SeekPlayerDecision.h"
#include "SeekCollectableDecision.h"
#include "FleeState.h"
#include "FleePlayerDecision.h"
#include "fleeItemDecision.h"
#include "SeekItemDecision.h"
#include "Object.h"
#include <iostream>
#include "Collectable.h"
#include <sstream>
#include "PhysicsEntity.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an Enemy object. Initialises Entity and SM
Enemy::Enemy(std::string name, vector3df startPos, float velMod) : Entity(-1, 0, name), _stateMachine(this){
	_enemyName = name;
	_velMod = velMod;
	_startPos = startPos;
}

//Initialise the enemy and add states to SM

void Enemy::initialise(){
	// find player pointer
	Entity* player = EntityManager::getNamedEntities("Player")->front();

	//find object pointers
	std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
	Object* fish = 0;
	Object* spray = 0;
	Object* bone = 0;
	Object* carrot = 0;
	auto iter = objects->begin();
	while (iter != objects->end()){
		Object* temp = (Object*)(*iter);
		if (temp->getItemName() == "fish"){
			fish = temp;
		}
		if (temp->getItemName() == "spray"){
			spray = temp;
		}
		if (temp->getItemName() == "bone"){
			bone = temp;
		}
		if (temp->getItemName() == "carrot"){
			carrot = temp;
		}
		iter++;
	}

	//find socks
	std::list<Entity*>* collectables = EntityManager::getNamedEntities("Collectable");
	Collectable* socks = 0;
	Collectable* shirt = 0;
	Collectable* jeans = 0;
	Collectable* shoes = 0;
	auto cIter = collectables->begin();
	while (cIter != collectables->end()){
		Collectable* tempC = (Collectable*)(*cIter);
		if (tempC->getItemName() == "socks"){
			socks = tempC;
		}
		if (tempC->getItemName() == "shirt"){
			shirt = tempC;
		}
		if (tempC->getItemName() == "jeans"){
			jeans = tempC;
		}
		if (tempC->getItemName() == "shoes"){
			shoes = tempC;
		}
		cIter++;
	}


	//Add states to SM
	if (_enemyName == "cat"){// seeks socks, hates spray
		_stateMachine.addState("Normal", new StateNormal());
		_stateMachine.addState("SeekPlayer", new SeekState(this, player, _velMod));
		_stateMachine.addState("SeekItem", new SeekState(this, fish, _velMod));
		_stateMachine.addState("FleePlayer", new FleeState(this, player, _velMod));
		_stateMachine.addState("FleeItem", new FleeState(this, spray, _velMod));
		_stateMachine.addState("SeekCollectable", new SeekState(this, socks, _velMod));
	}
	else if (_enemyName == "fatcat"){// seeks shirt, loves fish
		_stateMachine.addState("Normal", new StateNormal());
		_stateMachine.addState("SeekItem", new SeekState(this, fish, _velMod));
		_stateMachine.addState("SeekCollectable", new SeekState(this, shirt, _velMod));
	}
	else if (_enemyName == "rabbit"){//seeks jeans, loves carrots
		_stateMachine.addState("Normal", new StateNormal());
		_stateMachine.addState("SeekPlayer", new SeekState(this, player, _velMod));
		_stateMachine.addState("FleePlayer", new FleeState(this, player, _velMod));
		_stateMachine.addState("SeekItem", new SeekState(this, carrot, _velMod));
		_stateMachine.addState("SeekCollectable", new SeekState(this, jeans, _velMod));
	}
	else if (_enemyName == "dog"){// seeks shoes, loves bones
		_stateMachine.addState("Normal", new StateNormal());
		_stateMachine.addState("SeekPlayer", new SeekState(this, player, _velMod));
		_stateMachine.addState("FleePlayer", new FleeState(this, player, _velMod));
		_stateMachine.addState("SeekItem", new SeekState(this, bone, _velMod));
		_stateMachine.addState("SeekCollectable", new SeekState(this, shoes, _velMod));
	}

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

	_rigidBody = PhysicsEngine::createBoxRigidBody(this, vector3df(1.0f, 1.0f, 1.0f), 1);
	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Enemy");
	physicsEntity->setRigidBody(_rigidBody);

}

//updates the enemy
void Enemy::update(float deltaTime){
	// Add elapsed time
	_elapsedTime += deltaTime;

	// Run AI every half second

	float freq = 1/60;
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
			new DistanceToFishDecision(
			10.0f,
			new DistanceToFishDecision(
			2.0f,
			new NormalDecision(),
			new SeekItemDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "dog"){
		result = new DistanceToPlayerDecision(
			30.0f,
			new DistanceToBoneDecision(
			10.0f,
			new DistanceToBoneDecision(
			2.0f,
			new NormalDecision(),
			new SeekItemDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "rabbit"){
		result = new DistanceToPlayerDecision(
			30.0f,
			new DistanceToCarrotDecision(
			10.0f,
			new DistanceToCarrotDecision(
			2.0f,
			new NormalDecision(),
			new SeekItemDecision()),
			new NormalDecision()),
			new NormalDecision());
	}

	if (name == "cat"){// will watch over socks, moving towards player then back to socks. Will Avoid spray at all costs...
		result = new DistanceToPlayerDecision(
			15.0f,
			new DistanceToSprayDecision(
			10.0f,
			new FleeItemDecision(),
			new DistanceToSocksDecision(
			5.0f,
			new SeekPlayerDecision(),
			new SeekCollectableDecision()
			)
			),
			new NormalDecision()
			);
	}

	return result;
}
