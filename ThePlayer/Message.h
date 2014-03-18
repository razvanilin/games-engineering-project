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