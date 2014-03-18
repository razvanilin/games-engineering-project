#pragma once

#include <irrlicht.h>

namespace GameEngine{
	class Camera{
	protected:
		//Camera node within Irrlicht
		irr::scene::ICameraSceneNode* _cameraNode;

		//3 values define a camera - position, target and which way is up
		irr::core::vector3df _position;
		irr::core::vector3df _target;
		irr::core::vector3df _up;

	public:

		Camera(){}
		virtual ~Camera(){}
		virtual void initialise() = 0;
		virtual void update(float deltaTime)=0;

		irr::core::vector3df getPosition(){return _position;}
		irr::core::vector3df getTarget(){return _target;}
		irr::core::vector3df getUp(){return _up;}

		void setPosition(const irr::core::vector3df val){_position = val;}
		void setTarget(const irr::core::vector3df val){_target = val;}
		void setUp(const irr::core::vector3df val){_up= val;}
	};
}