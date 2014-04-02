#pragma once

#include "Decision.h"
#include "Enemy.h"

using namespace GameEngine;

class DistanceToCarrotDecision : public Decision<Enemy>
{
private:
	float _distance;
protected:
	DecisionTreeNode<Enemy>* getBranch(Enemy* owner);
public:
	DistanceToCarrotDecision(float distance, DecisionTreeNode<Enemy>* trueNode, DecisionTreeNode<Enemy>* falseNode)
		: _distance(distance), Decision(trueNode, falseNode) { }
};