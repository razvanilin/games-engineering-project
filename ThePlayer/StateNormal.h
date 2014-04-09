/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once
#include "Enemy.h"

using namespace GameEngine;

class StateNormal : public State<Enemy>{
public:
	void execute(Enemy* owner, float deltaTime);
};