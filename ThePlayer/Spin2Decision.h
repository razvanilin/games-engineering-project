#pragma once

#include "DecisionTreeNode.h"
#include "Enemy.h"

using namespace GameEngine;

class Spin2Decision : public DecisionTreeNode<Enemy>
{
public:
	void makeDecision(Enemy* owner) { owner->getStateMachine().setState("Spin2"); }
};