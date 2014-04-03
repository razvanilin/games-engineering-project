#pragma once

#include <string>
#include <irrlicht.h>
#include "InputHandler.h"
#include "Camera.h"
#include <irrKlang.h>

namespace GameEngine
{
	class Game
	{
	private:
		// the underlying IttlichtDevice used for rendering
		irr::IrrlichtDevice* _device;
		//the window caption
		std::wstring _caption;
		//window dimensions
		irr::core::dimension2d<irr::u32> _dimensions;
		//camera
		Camera* _camera;
		//audio engine
		irrklang::ISoundEngine* _audioEngine;


	public:
		//create a Game class
		Game(){ }
		//destroys the Game class
		~Game(){ }
		// gets Irlicht device
		irr::IrrlichtDevice* getDevice(){ return _device; }
		//caption getter
		std::wstring getCaption() const { return _caption; }
		// caption setter
		void setCaption(const std::wstring& value){
			_caption = value;
		}
		//get screen dimensions
		irr::core::dimension2d<irr::u32> getDimensions() const{
			return _dimensions;
		}
		//set screen dimensions
		void setDimensions(const irr::core::dimension2d<irr::u32>& value){
			_dimensions = value;
		}
		//get and set camera
		Camera* getCam(){return _camera;}
		void setCam(Camera* val){_camera = val;}

		//get and set audio engine
		irrklang::ISoundEngine* getAudioEngine(){ return _audioEngine; }
		void setAudioEngine(irrklang::ISoundEngine* val){ _audioEngine = val; }


		//initialises the game
		bool initialise();
		//loads content associated with the game
		bool loadContent();
		//update stage of game
		bool update(float frameTime);
		//Render stage of game
		bool render();
		//Unloads game content
		void unloadContent();
		//shuts down the game
		void shutdown();
	};
}

extern GameEngine::Game game;
extern InputHandler inputHandler;