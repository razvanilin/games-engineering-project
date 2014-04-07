/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Entity.h"
#include "EntityManager.h"

namespace GameEngine{
	Entity::Entity(int id, irr::scene::ISceneNode* node, const std::string& name)
				:_id(id), _node(node), _name(name){

		//Every Entity calls this forcing it to be registered with EM
		EntityManager::registerEntity(this);
	}
}