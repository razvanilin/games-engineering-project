/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "PauseMenu.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace irr::gui;
using namespace irr::core;
using namespace irr::video;

const std::string BTN_PRESSED = "textures/button1.png";
const std::string BTN_DEFAULT = "textures/button0.png";

namespace GameEngine {
	enum {
		START,
		EXIT,
		EASY,
		MEDIUM,
		HARD,
		RESUME,
		MENU
	};

	bool PauseMenu::initialise() {
		
		_env = game.getDevice()->getGUIEnvironment();
		_font = _env->getFont("bigfont.png");
		return true;
	}

	bool PauseMenu::loadContent() {
		return true;
	}

	bool PauseMenu::update(float deltaTime) {
		dimension2d<u32> dims = game.getDimensions();

		// create the background image
		ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/logo.png");
		IGUIImage* img = _env->addImage(texture, position2d<s32>(500, 150), true);
		img->setUseAlphaChannel(true);

		// create buttons
		IGUIButton* resumeBtn = _env->addButton(recti(vector2di(100, 200), vector2di(350, 300)), 0, RESUME, L"Resume");
		resumeBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameResumed)
			resumeBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			resumeBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		return true;
	}

	void PauseMenu::unloadContent() {
//		_env->clear();
	}
}