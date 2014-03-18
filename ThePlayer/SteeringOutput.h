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