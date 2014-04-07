/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "State.h"
#include "Enemy.h"
#include "Seek.h"

using namespace GameEngine;

class SeekState : public State<Enemy>
{
private:
	Seek _seek;
public:
	SeekState(Enemy* owner, Entity* player, float maxSpeed)
		: _seek(owner, player, maxSpeed) { }
	~SeekState() { }
	void execute(Enemy* owner, float frameTime);
};