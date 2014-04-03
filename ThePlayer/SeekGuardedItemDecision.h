#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class SeekGuardedItemDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("SeekGuardedItem"); }
};