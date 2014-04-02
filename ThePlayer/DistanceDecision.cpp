#pragma once

#include "DistanceDecision.h"
#include "EntityManager.h"

DecisionTreeNode<Enemy>* DistanceDecision::getBranch(Enemy* owner)
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