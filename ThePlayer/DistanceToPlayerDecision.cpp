/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "DistanceToPlayerDecision.h"
#include "EntityManager.h"

DecisionTreeNode<Enemy>* DistanceToPlayerDecision::getBranch(Enemy* owner)
{
	Entity* player = EntityManager::getNamedEntities("Player")->front();
	vector3df playerPos = player->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toPlayer = playerPos - enemyPos;
	if (toPlayer.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}