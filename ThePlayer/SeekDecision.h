#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

class SeekDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { 
		owner->getStateMachine().setState("Seek"); 
		owner->setCurrentStateName("Seek");
	}
};