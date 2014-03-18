#pragma once

#include "Camera.h"

using namespace irr::core;

namespace GameEngine{
	class FreeCamera : public Camera{
	private:
		//yaw
		float _yaw;

		//pitch
		float _pitch;
		vector3df _translation;
	public:
		FreeCamera() : Camera(){}
		~FreeCamera(){}
		float getYaw(){return _yaw;}
		float getPitch(){return _pitch;}

		void setYaw(float val){_yaw = val;}
		void setPitch(float val){_pitch = val;}

		void initialise();
		void update(float deltaTime);
		void rotate(float deltaYaw, float deltaPitch);
		void move(vector3df translation);
	};
}