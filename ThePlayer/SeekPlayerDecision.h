#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class SeekPlayerDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) {
		owner->getStateMachine().setState("SeekPlayer");
		owner->setCurrentStateName("SeekPlayer");
	}
};