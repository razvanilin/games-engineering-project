
#include "DistanceToGuardedItemDecision.h"
#include "EntityManager.h"

DecisionTreeNode<Enemy>* DistanceToGuardedItemDecision::getBranch(Enemy* owner)
{

	vector3df GIPos = owner->getGuardedItem()->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toGI = GIPos - enemyPos;
	if (toGI.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}