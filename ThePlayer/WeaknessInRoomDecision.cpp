/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "WeaknessInRoomDecision.h"
#include "EntityManager.h"
#include "Object.h"

DecisionTreeNode<Enemy>* WeaknessInRoomDecision::getBranch(Enemy* owner)
{
	Object* weakness = (Object*)owner->getWeakness();
	vector3df playerPos = weakness->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toPlayer = playerPos - enemyPos;
	if (weakness->getCurrentRoom() == owner->getRoom()->getName())
		return _trueNode;
	else
		return _falseNode;
}