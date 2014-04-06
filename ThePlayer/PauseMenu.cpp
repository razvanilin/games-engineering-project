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
		ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg");
		IGUIImage* img = _env->addImage(texture, position2d<s32>(300, 150), true);

		// create buttons
		IGUIButton* resumeBtn = _env->addButton(recti(vector2di(100, 200), vector2di(350, 300)), 0, RESUME, L"Resume");
		resumeBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameResumed)
			resumeBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			resumeBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIButton* menuBtn = _env->addButton(recti(vector2di(100, 350), vector2di(350, 450)), 0, MENU, L"Main Menu");
		menuBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameMenu)
			menuBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			menuBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIStaticText* text = _env->addStaticText(L"Game Paused", rect<s32>(dims.Width / 2, dims.Height / 2, dims.Width / 1.5f, dims.Height / 1.5f), false);
		text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
		text->setOverrideFont(_font);

		return true;
	}

	void PauseMenu::unloadContent() {
//		_env->clear();
	}
}