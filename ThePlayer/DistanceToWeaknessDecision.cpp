/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "DistanceToWeaknessDecision.h"
#include "EntityManager.h"

DecisionTreeNode<Enemy>* DistanceToWeaknessDecision::getBranch(Enemy* owner)
{
	vector3df weaknessPos = owner->getWeakness()->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toWeak = weaknessPos - enemyPos;
	if (toWeak.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}