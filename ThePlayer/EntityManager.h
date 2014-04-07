/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once
#include <unordered_map>
#include "Entity.h"

namespace GameEngine{
	class EntityManager{
	private: 
		static int _nextID;
		static std::unordered_map<int, Entity*> _entities;
		static std::unordered_map<std::string, std::list<Entity*>> _namedEntities;
		EntityManager();
		~EntityManager();
	public:
		static bool initialise();
		static bool loadContent();
		static bool update(float deltaTime);
		static void unloadContent();
		static void shutdown();
		static void registerEntity(Entity* entity);
		static void removeEntity(Entity* entity);
		static Entity* getEntity(int id);
		static std::list<Entity*>* getNamedEntities(const std::string& name);
	};
}