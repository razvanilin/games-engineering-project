#include "FreeCamera.h"
#include "Game.h"

using namespace irr::core;
using namespace irr::scene;

namespace GameEngine{
	void FreeCamera::initialise(){
		_cameraNode = game.getDevice()->getSceneManager()->addCameraSceneNode();
	}

	void FreeCamera::update(float deltaTime){
		// Start with an identity matrix
		matrix4 mat = IdentityMatrix;

		//create transform matrix

		mat.setRotationRadians(vector3df(_pitch, _yaw, 2.0f));

		//transform the translation vector by this matrix to create movement
		mat.transformVect(_translation);

		//now add the translation vector to teh current position
		_position += _translation;

		//reset teh _translation
		_translation = vector3df(0.0f, 0.0f,0.0f);


		//create forward vector
		vector3df _forward(0.0f, 0.0f,1.0f);

		//transform this with the rotation matrix
		mat.transformVect(_forward);

		//Target is current position plus the transformed forward vector
		_target = _position + _forward;

		//do teh same for teh up vector
		_up = vector3df(0.0f, 1.0f, 0.0f);
		mat.transformVect(_up);

		//set camera values appropriately
		_cameraNode->setPosition(_position);
		_cameraNode->setTarget(_target);
		_cameraNode->setUpVector(_up);
	}
	void FreeCamera::rotate(float deltaYaw, float deltaPitch){
		_yaw += deltaYaw;
		_pitch += deltaPitch;
		//Limit pitch to avoid "looping through legs"
		if(_pitch <= -1)
			_pitch = -1;
		if (_pitch >= 1)
			_pitch = 1;
	}

	void FreeCamera::move(vector3df translation){
		_translation += translation;
	}
}