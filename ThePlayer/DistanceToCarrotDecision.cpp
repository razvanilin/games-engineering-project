#pragma once

#include "DistanceToCarrotDecision.h"
#include "EntityManager.h"
#include "Object.h"

DecisionTreeNode<Enemy>* DistanceToCarrotDecision::getBranch(Enemy* owner)
{

	std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
	Object* carrot = 0;
	auto iter2 = objects->begin();
	while (iter2 != objects->end()){
		Object* obj2 = (Object*)(*iter2);
		if (obj2->getItemName() == "carrot"){
			carrot = obj2;
			break;
		}
		iter2++;
	}


	vector3df carrotPos = carrot->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toCarrot = carrotPos - enemyPos;
	if (toCarrot.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}