#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class SeekWeaknessDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) {
		owner->getStateMachine().setState("SeekWeakness");
		owner->setCurrentStateName("SeekWeakness");
	}
};