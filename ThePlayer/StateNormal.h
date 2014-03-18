#pragma once
#include "Enemy.h"

using namespace GameEngine;

class StateNormal : public State<Enemy>{
public:
	void execute(Enemy* owner, float deltaTime);
};