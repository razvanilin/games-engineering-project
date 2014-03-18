#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

using namespace GameEngine;

class SpinDecision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("Spin"); }
};