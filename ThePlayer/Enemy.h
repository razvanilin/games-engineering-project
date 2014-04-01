#pragma once

#include "Entity.h"
#include "StateMachine.h"
#include "PhysicsEngine.h"
#include "DecisionTreeNode.h"

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
	//
	float _velMod;
	vector3df _startPos;



public:
	//constructor
	Enemy(std::string name, vector3df startPos, float pVel);
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

	std::string getEnemyName(){
		return _enemyName;
	}


	DecisionTreeNode<Enemy>* getDecTree(std::string name);
};