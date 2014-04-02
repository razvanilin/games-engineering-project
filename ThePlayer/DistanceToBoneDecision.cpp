#pragma once

#include "DistanceToBoneDecision.h"
#include "EntityManager.h"
#include "Object.h"

DecisionTreeNode<Enemy>* DistanceToBoneDecision::getBranch(Enemy* owner)
{

	std::list<Entity*>* objects = EntityManager::getNamedEntities("Object");
	Object* bone = 0;
	auto iter2 = objects->begin();
	while (iter2 != objects->end()){
		Object* obj2 = (Object*)(*iter2);
		if (obj2->getItemName() == "bone"){
			bone = obj2;
			break;
		}
		iter2++;
	}

	vector3df bonePos = bone->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toBone = bonePos - enemyPos;
	if (toBone.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}