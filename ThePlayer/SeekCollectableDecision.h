#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class SeekCollectableDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("SeekCollectable"); }
};