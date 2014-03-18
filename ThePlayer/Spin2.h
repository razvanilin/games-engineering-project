#pragma once

#include "Enemy.h"

class Spin2 : public State<Enemy>
{
private:
	btVector3 _angular;
public:
	Spin2() : _angular(btVector3(10.0f, 0.0f, 0.0f)) { }
	void execute(Enemy* owner, float deltaTime);
};