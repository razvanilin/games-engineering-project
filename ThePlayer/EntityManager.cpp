#include "EntityManager.h"
#include <iostream>
#include <unordered_map>

namespace GameEngine{
	//initialise static attributes
	int EntityManager::_nextID = 0;
	std::unordered_map<int, Entity*> EntityManager::_entities = std::unordered_map<int, Entity*>();
	std::unordered_map<std::string, std::list<Entity*>> EntityManager::_namedEntities = std::unordered_map<std::string, std::list<Entity*>>();

	// constructor is empty
	EntityManager::EntityManager(){ }

	//destructor is empty
	EntityManager::~EntityManager(){ }

	bool EntityManager::initialise(){
		//initialise all entities using an iterator
		std::unordered_map<int, Entity*>::iterator iter = _entities.begin();
		for(; iter!=_entities.end(); ++iter){
			iter->second->initialise();
		}
		return true;
	}

	bool EntityManager::loadContent(){
		//iterate over all entities and call loadContent() on each
		std::unordered_map<int, Entity*>::iterator i = _entities.begin();
		for(; i!=_entities.end(); ++i){
			i->second->loadContent();
		}
		return true;
	}

	bool EntityManager::update(float deltaTime){
		//shorten the iteration process and include in the for loop
		for(auto i=_entities.begin(); i!=_entities.end(); ++i){
			i->second->update(deltaTime);
		}
		return true;
	}
	void EntityManager::unloadContent(){
		for(auto i=_entities.begin(); i!=_entities.end();++i){
			i->second->unloadContent();		
		}
	}
	void EntityManager::shutdown(){
		for(auto i=_entities.begin(); i!=_entities.end(); ++i){
			//delete entity to release memory
			delete i->second;
			i->second = 0;
		}
		//now to clear the map emptying the contents
		_entities.clear();
	}
	void EntityManager::registerEntity(Entity* entity){
		// check if Id needs allocated
		if(entity->getID() == -1){
			//No ID allocated - find next available
			while(_entities.find(_nextID)!=_entities.end()){
				++_nextID;
			}
			entity->setID(_nextID++);
		}
		//otherwise check ID is not already in use
		else if (_entities.find(entity->getID()) != _entities.end()){
			//diplay error and return
			std::cerr << "Error registering entity of ID: " + entity->getID() << std::endl;
			return;
		}
		//if it gets this far, all is good so add to map
		_entities[entity->getID()] = entity;

		//now check it has a name

		if(entity->getName() != ""){
			//entity has a name  - check if others exist
			auto found = _namedEntities.find(entity->getName());
			if(found != _namedEntities.end()){
				//we have discovered other entities with the same name - push it to the back of this list
				found->second.push_back(entity);
			}else{
				// no existing name found, create new list and index
				std::list<Entity*> templist;
				templist.push_back(entity);
				_namedEntities[entity->getName()] = templist;
			}
		}
	}

	void EntityManager::removeEntity(Entity* entity){
		auto found = _entities.find(entity->getID());
		if (found != _entities.end()){
			_entities.erase(found);
		}

		// now remove from named entities
		if(entity->getName() != ""){
			//find the list of correctly named entities
			auto found = _namedEntities.find(entity->getName());
			found->second.remove(entity);
		}
	}

	Entity* EntityManager::getEntity(int id){
		auto found = _entities.find(id);
		if (found!=_entities.end())
			return found->second;
		//entity doesn't exist - return 0
		return 0;
	}

	std::list<Entity*>* EntityManager::getNamedEntities(const std::string& name){
		//find the list of entities with the given name
		auto found = _namedEntities.find(name);

		//check we have a list
		if(found != _namedEntities.end())
			return &(found->second);
		else
			return 0;
		
	}
}