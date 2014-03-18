#include "TargetCamera.h"
#include "Game.h"

using namespace irr::core;
using namespace irr::scene;

namespace GameEngine{
	void TargetCamera::initialise(){
		_cameraNode = game.getDevice()->getSceneManager()->addCameraSceneNode();
	}

	void TargetCamera::update(float DeltaTime){
		//Calculate the forward direction based on our target and position
		vector3df forward = _target - _position;
		//calculate the side direction based on the normal and forward direction
		vector3df side = vector3df(0.0f, 1.0f, 0.0f).crossProduct(forward);
		//up vector usinf forward and side. Again use cross product to get vector orthogonal to the original ones
		_up = forward.crossProduct(side);
		//now set the values in camera node
		_cameraNode->setPosition(_position);
		_cameraNode->setTarget(_target);
		_cameraNode->setUpVector(_up);
	}
}
