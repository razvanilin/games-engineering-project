/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include <string>

using namespace std;

namespace GameEngine{
	//forward declaration  for the Entity class
	class Entity;

	struct Message{
		Entity* entity;
		std::string message;
		void* data;

		Message(Entity* entity, const std::string& message, void* data)
			: entity(entity), message(message), data(data){
		
		}
	};
}