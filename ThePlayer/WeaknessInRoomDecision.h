/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
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