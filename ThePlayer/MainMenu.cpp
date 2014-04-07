#include "MainMenu.h"
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
		HARD
	};

	bool MainMenu::initialise() {
		_env = game.getDevice()->getGUIEnvironment();
		_font = _env->getFont("bigfont.png");

		return true;
	}

	bool MainMenu::loadContent() {
		return true;
	}

	bool MainMenu::update(float deltaTime) {
		dimension2d<u32> dims = game.getDimensions();

		// create the background image
		ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/logo.png");
		IGUIImage* img = _env->addImage(texture, position2d<s32>(500,  300), true);
		img->setUseAlphaChannel(true);

		// create the start and exit buttons
		IGUIButton* startBtn = _env->addButton(recti(vector2di(100, 200), vector2di(350, 300)), 0, START, L"Start Game");
		startBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameStarted)
			startBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			startBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));
		startBtn->setScaleImage(false);
		startBtn->setUseAlphaChannel(true);

		IGUIButton* exitBtn = _env->addButton(recti(vector2di(100, 400), vector2di(350, 500)), 0, EXIT, L"Exit Game");
		exitBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameClosed)
			exitBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			exitBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));
		exitBtn->setScaleImage(false);
		exitBtn->setUseAlphaChannel(true);

		// create the difficulty buttons
		IGUIButton* easyBtn = _env->addButton(recti(vector2di(400, 200), vector2di(550, 250)), 0, EASY, L"Easy");
		easyBtn->setOverrideFont(_font);
		easyBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIButton* mediumBtn = _env->addButton(recti(vector2di(560, 200), vector2di(710, 250)), 0, MEDIUM, L"Medium");
		mediumBtn->setOverrideFont(_font);
		mediumBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIButton* hardBtn = _env->addButton(recti(vector2di(720, 200), vector2di(870, 250)), 0, HARD, L"Hard");
		hardBtn->setOverrideFont(_font);
		hardBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		if (inputHandler.getGameState().GameDifficulty == "easy")
			easyBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else if (inputHandler.getGameState().GameDifficulty == "medium")
			mediumBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else if (inputHandler.getGameState().GameDifficulty == "hard")
			hardBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));

		return true;
	}
}