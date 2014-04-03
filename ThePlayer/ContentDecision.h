#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

using namespace GameEngine;

class ContentDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) {
		owner->getStateMachine().setState("Normal");
		owner->setCurrentStateName("Content");
	}
};