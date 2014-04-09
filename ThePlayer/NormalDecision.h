/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

using namespace GameEngine;

class NormalDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { 
		owner->getStateMachine().setState("Normal"); 
		owner->setCurrentStateName("Normal");
	}
};