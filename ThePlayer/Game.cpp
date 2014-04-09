/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "Game.h"
#include "EntityManager.h"
#include "InputHandler.h"
#include "MessageHandler.h"
#include "PhysicsEngine.h"
#include "MainMenu.h"
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
			false,
			true,
			&inputHandler);
		if (!_device){
			std::cerr << "Error creating device" << std::endl;
			return false;
		}
		_device->setWindowCaption(_caption.c_str());

		//initialise the PhysicsEngine
		if (!PhysicsEngine::initialise()){
			return false;
		}

		//initialisation of EntityManager
		if (!EntityManager::initialise()){
			return false;
		}
		//Initialise the camera
		_camera->initialise();

		// initialise the messageHandler
		MessageHandler::initialise();

		//initialise AudioEngine
		_audioEngine = irrklang::createIrrKlangDevice();

		// initialises the menu


		// initialises the pause menu

		//seed the random function
		srand(time(NULL));
		return true;
	}
	int i = 0;
	bool Game::loadContent(){
		if (!EntityManager::loadContent()) return false;
		return true;
	}

	bool gamePaused = false;
	bool Game::update(float frameTime){

		if (inputHandler.getGameState().GameStarted && !inputHandler.getGameState().GamePaused && !inputHandler.getGameState().GameEnded) {
			if (!PhysicsEngine::update(frameTime)) return false;
			if (!EntityManager::update(frameTime)) return false;
			_camera->update(frameTime);
			MessageHandler::update();
		}
		else if (inputHandler.getGameState().GamePaused) {
			if (i == 0) {
				_pause = new PauseMenu();
				_pause->initialise();
			}
			_pause->update(frameTime);
			i++;
		}
		else if (inputHandler.getGameState().GameMenu){
			if (i == 0) {
				_menu = new MainMenu();
				_menu->initialise();
			}
			_menu->update(frameTime);
			i++;
		}
		else if (inputHandler.getGameState().GameEnded) {
			if (i == 0) {
				_end = new EndGame(_endCause, _noiseMade);
				//_end->initialise();
			}
			_end->update(frameTime);
			i++;
		}
		inputHandler.update();
		i = 0;

		return true;
	}

	bool Game::render(){

		if (!_device->getVideoDriver()->beginScene()) return false;
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
		if (!_device->getVideoDriver()->endScene()) return false;

		return true;
	}

	void Game::unloadContent(){
		EntityManager::unloadContent();
		_pause->unloadContent();
	}

	void Game::shutdown(){
		PhysicsEngine::shutdown();
		EntityManager::shutdown();
		_device->drop();
		_audioEngine->drop();
	}
}