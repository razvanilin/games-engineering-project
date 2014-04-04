#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class FleeWeaknessDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) {
		owner->getStateMachine().setState("FleeWeakness"); 
		owner->setCurrentStateName("FleeWeakness");
	}
};