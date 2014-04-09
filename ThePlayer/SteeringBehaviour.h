/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include "SteeringOutput.h"

namespace GameEngine
{
	class SteeringBehaviour
	{
	public:
		// Destructor is virtual. This is a base class
		virtual ~SteeringBehaviour() { }
		// Pure virtual function used to get steering output
		virtual SteeringOutput getSteering() = 0;
	};
}
