
#include "DistanceToSocksDecision.h"
#include "EntityManager.h"
#include "Collectable.h"

DecisionTreeNode<Enemy>* DistanceToSocksDecision::getBranch(Enemy* owner)
{

	std::list<Entity*>* collectables = EntityManager::getNamedEntities("Collectable");
	Collectable* socks = 0;
	auto sockIter = collectables->begin();
	while (sockIter != collectables->end()){
		Collectable* possSocks = (Collectable*)(*sockIter);
		if (possSocks->getItemName() == "socks"){
			socks = possSocks;
			break;
		}
		sockIter++;
	}


	vector3df socksPos = socks->getNode()->getPosition();
	vector3df enemyPos = owner->getNode()->getPosition();
	vector3df toSocks = socksPos - enemyPos;
	if (toSocks.getLength() < _distance)
		return _trueNode;
	else
		return _falseNode;
}