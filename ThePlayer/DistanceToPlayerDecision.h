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

class DistanceToPlayerDecision : public Decision<Enemy>
{
private:
	float _distance;
protected:
	DecisionTreeNode<Enemy>* getBranch(Enemy* owner);
public:
	DistanceToPlayerDecision(float distance, DecisionTreeNode<Enemy>* trueNode, DecisionTreeNode<Enemy>* falseNode)
		: _distance(distance), Decision(trueNode, falseNode) { }
};