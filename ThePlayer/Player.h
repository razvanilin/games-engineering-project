#pragma once

#include "Entity.h"

using namespace GameEngine;

class Player : public Entity{
public:
	Player() : Entity(-1, 0, "Player"){}
	void initialise();
	void loadContent();
	void update(float deltaTime);
	void unloadContent(){}
};