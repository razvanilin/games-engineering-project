#pragma once
#include "Enemy.h"

using namespace GameEngine;

class StateSpin : public State<Enemy>{
public:
	void execute(Enemy* owner, float deltaTime);
};