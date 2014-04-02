#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class FleeDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("Flee"); }
};