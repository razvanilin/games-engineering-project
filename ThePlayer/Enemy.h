#pragma once

#include "Entity.h"
#include "StateMachine.h"
#include "PhysicsEngine.h"
#include "DecisionTreeNode.h"
#include "Collectable.h"
#include "Object.h"
#include "Room.h"

using namespace GameEngine;

class Enemy : public Entity{
private:

	//StsteMachine to control behaviour
	StateMachine<Enemy> _stateMachine;
	//Decision tree used to determine which state to enter(AI)
	DecisionTreeNode<Enemy>* _decisionTree;
	//Rigidbody controlling movement (physics)
	btRigidBody* _rigidBody;
	// Keep track of total elapsed time since last decision
	float _elapsedTime;
	//name for AI
	std::string _enemyName;
	//current state name
	std::string _currentState;

	//
	float _velMod;
	vector3df _startPos;
	Collectable* _guardedItem;
	Object* _weakness;
	Room* _room;



public:
	//constructor
	Enemy(std::string name, Room* room, vector3df startPos, float pVel, Object* weakness, Collectable* guardedItem);
	//destructor
	~Enemy(){}
	//RB getter
	btRigidBody* getRigidBody(){ return _rigidBody; }
	// Gets the state machine of the enemy
	StateMachine<Enemy>& getStateMachine() { return _stateMachine; }
	//initialise
	void initialise();
	//Loads any content
	void loadContent();
	//Updates enemy
	void update(float deltaTime);
	//Unloads anything not handled by Irrlicht or Bullet
	void unloadContent(){}
	//get guarded item
	Collectable* getGuardedItem(){ return _guardedItem; }
	//get weaknes
	Object* getWeakness(){ return _weakness; }
	void Enemy::handleMessage(const Message& message);

	//get/set room
	Room* getRoom(){ return _room; }
	void setRoom(Room* val){ _room = val; }

	//get/set currentStateName
	std::string getCurrentStateName(){ return _currentState; }
	void setCurrentStateName(std::string val){ _currentState = val; }

	std::string getEnemyName(){
		return _enemyName;
	}


	DecisionTreeNode<Enemy>* getDecTree(std::string name);
};