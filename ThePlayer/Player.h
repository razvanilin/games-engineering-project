#pragma once

#include "Entity.h"
#include "Object.h"

using namespace GameEngine;

class Player : public Entity{
private:
	bool _isCarrying;
	Object* _carriedItem;
	std::list<std::string> _collectedItems;
public:
	Player() : Entity(-1, 0, "Player"){
		_isCarrying = false;
	}
	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent(){}
	Object* getCarriedItem(){ return _carriedItem; }
	void setCarriedItem(Object* val){ _carriedItem = val; }
	void clearCarriedItem(){ _carriedItem = 0; }
	void addItem(std::string val){ _collectedItems.push_front(val); }
	std::list<std::string> getCollectedItems(){ return _collectedItems; }

};