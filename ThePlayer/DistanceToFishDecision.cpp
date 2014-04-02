#pragma once

#include "DistanceToFishDecision.h"
#include "EntityManager.h"
#include "Object.h"

DecisionTreeNode<Enemy>* DistanceToFishDecision::getBranch(Enemy* owner)
{

	std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
	Object* fish = 0;
	auto iter2 = objects->begin();
	while (iter2 != objects->end()){
		Object* obj2 = (Object*)(*iter2);
		if (obj2->getItemName() == "fish"){
			fish = obj2;
			break;
		}
		iter2++;
	}


	vector3df fishPos = fish->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toFish = fishPos - enemyPos;
	if (toFish.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}