#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class FleeItemDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("FleeItem"); }
};