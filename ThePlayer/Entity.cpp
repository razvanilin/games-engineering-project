#include "Entity.h"
#include "EntityManager.h"

namespace GameEngine{
	Entity::Entity(int id, irr::scene::IMeshSceneNode* node, const std::string& name)
				:_id(id), _node(node), _name(name){

		//Every Entity calls this forcing it to be registered with EM
		EntityManager::registerEntity(this);
	}
}