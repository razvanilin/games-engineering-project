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