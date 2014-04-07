/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include <irrlicht.h>

using namespace irr::core;

namespace GameEngine
{
	struct SteeringOutput
	{
		// The direction to travel in
		vector3df direction;
		// Rotation to face direction. This is y-axis rotation
		float rotation;
	};
}