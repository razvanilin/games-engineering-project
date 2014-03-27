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
#include "DistanceDecision.h"
#include "RandomDecision.h"
#include "SeekState.h"
#include "SeekDecision.h"
#include "FleeState.h"
#include "FleeDecision.h"
#include "PhysicsEntity.h"

using namespace irr::core;
using namespace irr::scene;
using namespace irr::video;

//Creates an Enemy object. Initialises Entity and SM
Enemy::Enemy() : Entity(-1, 0, ""), _stateMachine(this){
	
}

//Initialise the enemy and add states to SM

void Enemy::initialise(){
	Entity* player = EntityManager::getNamedEntities("Object")->front();
	//Add states to SM
	_stateMachine.addState("Normal", new StateNormal());
	_stateMachine.addState("Seek", new SeekState(this, player, 10.0f));
	_stateMachine.addState("Flee", new FleeState(this, player, 10.0f));
	//set initial state to normal
	_stateMachine.setState("Normal");
	// Set elapsed time to 0
	_elapsedTime = 0.0f;
	// Create decision tree
	_decisionTree = new DistanceDecision(
		20.0f,
		new DistanceDecision(
		10.0f,
		new FleeDecision(),
		new RandomDecision<Enemy>(
			new NormalDecision(),
			new SeekDecision())),
		new SeekDecision());
}

//Load content for the enemy
void Enemy::loadContent(){
	//make a sphere
	_node = game.getDevice()->getSceneManager()->addSphereSceneNode(1.0f, 32);
	//set position to (0,0,0)
	_node->setPosition(vector3df(0.0f, 0.0f, 0.0f));
	//set material properties
	_node->setMaterialFlag(EMF_LIGHTING, false);
	_node->setMaterialTexture(0, game.getDevice()->getVideoDriver()->getTexture("textures/flame.jpg"));
	//create rigid body (sphere with rad of 1)
	_rigidBody = PhysicsEngine::createSphereRigidBody(this, 1.0f, 10);

	PhysicsEntity* physicsEntity = new PhysicsEntity(_node, "Enemy");
	physicsEntity->setRigidBody(_rigidBody);
}

//updates the enemy
void Enemy::update(float deltaTime){
	// update our position and orientation from PhysicsEngines rigid body
	btVector3 point = _rigidBody->getCenterOfMassPosition();
	_node->setPosition(vector3df(point.getX(), point.getY(), point.getZ()));
	const btQuaternion quat = _rigidBody->getOrientation();
	quaternion q(quat.getX(),quat.getY(),quat.getZ(),quat.getW());
	vector3df eular;
	q.toEuler(eular);
	eular *= RADTODEG;
	_node->setRotation(eular);

	// Add elapsed time
	_elapsedTime += deltaTime;

	// Run AI every half second
	if (_elapsedTime > 0.5f)
	{
		// Make decision
		_decisionTree->makeDecision(this);
		// Execute state
		_stateMachine.update(deltaTime);
		// Reset elapsed time
		_elapsedTime = 0.0f;
	}

	/*
	//if close to the player, set state to spin
	Entity* player = EntityManager::getNamedEntities("Player")->front();
	vector3df playerPos = player->getNode()->getPosition();
	vector3df distance = playerPos - _node->getPosition();

	if (distance.getLength() <= 10.0f){
		_stateMachine.setState("Spin");
	}else{
		_stateMachine.setState("Normal");
	}
	*/
}