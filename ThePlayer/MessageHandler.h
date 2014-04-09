/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "Entity.h"
#include <string>
#include <queue>
#include "Message.h"

namespace GameEngine{
	class MessageHandler{
	private:
		static std::queue<Message> _messages;
		MessageHandler(){}
	public:
		~MessageHandler();
		static void initialise();
		static void update();
		static void sendMessage(const Message& message);

		
	};
}