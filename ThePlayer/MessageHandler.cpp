/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "MessageHandler.h"
#include "Entity.h"
#include "Game.h"

namespace GameEngine{
	std::queue<Message> MessageHandler::_messages =  std::queue<Message>();

	MessageHandler::~MessageHandler(){
		while(!_messages.empty()){
			_messages.pop();
		}
	}

	void MessageHandler::initialise(){
		// Nothing to initialise
	}

	void MessageHandler::update(){
		//Loop thru message Q until out of messages
		while(!_messages.empty()){
			Message message = _messages.front();
			//remove it from the Q
			_messages.pop();
			//send the message to the respecitve entity
			message.entity->handleMessage(message);
		}
	}

	void MessageHandler::sendMessage(const Message& message){
		// Push into queue
		_messages.push(message);
	}
}