/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once

#include <irrlicht.h>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace irr::gui;
using namespace irr::core;

namespace GameEngine {
	class EndGame {

	private:
		IGUIEnvironment* _env;
		IGUIFont* _font;
		dimension2d<irr::u32> _dimensions;
		std::unordered_map<std::string, std::string> _caption;
		std::string _endCause;
		float _noiseMade;

	public:
		EndGame(std::string endCause, float noiseMade);
		
		~EndGame() {}

		bool initialise();
		bool loadContent();
		bool update(float deltaTime);
		bool render();
		void unloadContent();
		void shutdown();
	};
}