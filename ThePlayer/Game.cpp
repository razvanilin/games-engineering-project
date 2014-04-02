#include "Game.h"
#include "EntityManager.h"
#include "InputHandler.h"
#include "MessageHandler.h"
#include "PhysicsEngine.h"
#include <ctime>

#include <iostream>

using namespace GameEngine;

GameEngine::Game game = GameEngine::Game();
InputHandler inputHandler = InputHandler();

namespace GameEngine{
	bool Game::initialise(){
		_device = irr::createDevice(
			irr::video::EDT_DIRECT3D9,
			_dimensions,
			32,
			false,
			true,
			0,
			&inputHandler);
		if(!_device){
			std::cerr << "Error creating device" << std::endl;
			return false;
		}
		_device->setWindowCaption(_caption.c_str());

		//initialise the PhysicsEngine
		if(!PhysicsEngine::initialise()){
			return false;
		}

		//initialisation of EntityManager
		if(!EntityManager::initialise()){
			return false;
		}
		//Initialise the camera
		_camera->initialise();

		// initialise the messageHandler
		MessageHandler::initialise();

		//seed the random function
		srand(time(NULL));
		return true;
	}
	
	bool Game::loadContent(){
		if(!EntityManager::loadContent()) return false;
		return true;
	}

	bool Game::update(float frameTime){
		if(!PhysicsEngine::update(frameTime)) return false;
		if(!EntityManager::update(frameTime)) return false;
		inputHandler.update();
		_camera->update(frameTime);
		MessageHandler::update();
		return true;
	}

	bool Game::render(){
		if(!_device->getVideoDriver()->beginScene()) return false;
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
		if(!_device->getVideoDriver()->endScene()) return false;
		return true;
	}

	void Game::unloadContent(){
		EntityManager::unloadContent();
	}

	void Game::shutdown(){
		PhysicsEngine::shutdown();
		EntityManager::shutdown();
		_device->drop();
	}
}