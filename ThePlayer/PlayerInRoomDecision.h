#pragma once

#include "Decision.h"
#include "Enemy.h"

using namespace GameEngine;

class PlayerInRoomDecision : public Decision<Enemy>
{
private:

protected:
	DecisionTreeNode<Enemy>* getBranch(Enemy* owner);
public:
	PlayerInRoomDecision(DecisionTreeNode<Enemy>* trueNode, DecisionTreeNode<Enemy>* falseNode)
		: Decision(trueNode, falseNode) { }
};