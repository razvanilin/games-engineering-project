#pragma once

#include "Camera.h"

namespace GameEngine{
	class TargetCamera : public Camera{
	public:
		TargetCamera() : Camera() { }
		~TargetCamera(){}
		void initialise();
		void update(float deltaTime);
	};
}