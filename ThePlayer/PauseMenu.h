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

using namespace irr::gui;
using namespace irr::core;

namespace GameEngine {
	class PauseMenu {

	private:
		IGUIEnvironment* _env;
		IGUIFont* _font;
		dimension2d<irr::u32> _dimensions;

	public:
		PauseMenu() {}
		~PauseMenu() {}

		bool initialise();
		bool loadContent();
		bool update(float deltaTime);
		bool render();
		void unloadContent();
		void shutdown();
	};
}