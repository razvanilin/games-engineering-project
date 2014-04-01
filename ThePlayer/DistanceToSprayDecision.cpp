#pragma once

#include "DistanceToSprayDecision.h"
#include "EntityManager.h"
#include "Object.h"

DecisionTreeNode<Enemy>* DistanceToSprayDecision::getBranch(Enemy* owner)
{

	std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
	Object* spray = 0;
	auto iter2 = objects->begin();
	while (iter2 != objects->end()){
		Object* obj2 = (Object*)(*iter2);
		if (obj2->getItemName() == "spray"){
			spray = obj2;
			break;
		}
		iter2++;
	}


	vector3df sprayPos = spray->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toSpray = sprayPos - enemyPos;
	if (toSpray.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}