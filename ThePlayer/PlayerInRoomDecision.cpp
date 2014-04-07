/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "PlayerInRoomDecision.h"
#include "EntityManager.h"
#include "Player.h"

DecisionTreeNode<Enemy>* PlayerInRoomDecision::getBranch(Enemy* owner)
{
	Player* player = (Player*)EntityManager::getNamedEntities("Player")->front();
	vector3df playerPos = player->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toPlayer = playerPos - enemyPos;
	if (player->getCurrentRoom() == owner->getRoom()->getName())
		return _trueNode;
	else
		return _falseNode;
}