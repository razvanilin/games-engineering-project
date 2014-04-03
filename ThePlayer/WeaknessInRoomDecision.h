#pragma once

#include "Decision.h"
#include "Enemy.h"

using namespace GameEngine;

class WeaknessInRoomDecision : public Decision<Enemy>
{
private:

protected:
	DecisionTreeNode<Enemy>* getBranch(Enemy* owner);
public:
	WeaknessInRoomDecision(DecisionTreeNode<Enemy>* trueNode, DecisionTreeNode<Enemy>* falseNode)
		: Decision(trueNode, falseNode) { }
};