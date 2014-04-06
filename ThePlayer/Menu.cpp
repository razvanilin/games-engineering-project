#include "Menu.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include <string>

using namespace irr::gui;
using namespace irr::core;
using namespace irr::video;

GameEngine::Menu menu = GameEngine::Menu();
InputHandler inputHandlerMenu = InputHandler();

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
	bool Menu::initialise() {
		_device = irr::createDevice(
			EDT_DIRECT3D9,
			_dimensions,
			32,
			false,
			false,
			true,
			&inputHandlerMenu);
		if (!_device) {
			std::cerr << "Error creating device" << std::endl;
			return false;
		}
		_device->setWindowCaption(_caption.c_str());

		_env = _device->getGUIEnvironment();

		_audioEngine = irrklang::createIrrKlangDevice();
		return true;
	}

	bool Menu::loadContent() {
		return true;
	}

	bool Menu::update(float deltaTime) {
		dimension2d<u32> dims = game.getDimensions();

		// create the background image
		ITexture* texture = menu.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg");
		IGUIImage* img = _env->addImage(texture, position2d<s32>(300, 150), true);

		// create the start and exit buttons
		IGUIButton* startBtn = _env->addButton(recti(vector2di(100, 200), vector2di(350, 300)), 0, START, L"Start Game");
		startBtn->setOverrideFont(_env->getFont("bigfont.png"));
		if (inputHandlerMenu.getGameState().GameStarted)
			startBtn->setImage(_device->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			startBtn->setImage(_device->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));
		startBtn->setScaleImage(false);
		startBtn->setUseAlphaChannel(true);

		IGUIButton* exitBtn = _env->addButton(recti(vector2di(100, 400), vector2di(350, 500)), 0, EXIT, L"Exit Game");
		exitBtn->setOverrideFont(_env->getFont("bigfont.png"));
		if (inputHandlerMenu.getGameState().GameClosed)
			exitBtn->setImage(_device->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			exitBtn->setImage(_device->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));
		exitBtn->setScaleImage(false);
		exitBtn->setUseAlphaChannel(true);

		// create the difficulty buttons
		IGUIButton* easyBtn = _env->addButton(recti(vector2di(400, 200), vector2di(550, 250)), 0, EASY, L"Easy");
		easyBtn->setOverrideFont(_env->getFont("bigfont.png"));
		easyBtn->setImage(_device->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIButton* mediumBtn = _env->addButton(recti(vector2di(560, 200), vector2di(710, 250)), 0, MEDIUM, L"Medium");
		mediumBtn->setOverrideFont(_env->getFont("bigfont.png"));
		mediumBtn->setImage(_device->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		IGUIButton* hardBtn = _env->addButton(recti(vector2di(720, 200), vector2di(870, 250)), 0, HARD, L"Hard");
		hardBtn->setOverrideFont(_env->getFont("bigfont.png"));
		hardBtn->setImage(_device->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		if (inputHandlerMenu.getGameState().GameDifficulty == "easy")
			easyBtn->setImage(_device->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else if (inputHandlerMenu.getGameState().GameDifficulty == "medium")
			mediumBtn->setImage(_device->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else if (inputHandlerMenu.getGameState().GameDifficulty == "hard")
			hardBtn->setImage(_device->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));

		inputHandlerMenu.update();
		return true;
	}

	bool Menu::render() {
		if (!_device->getVideoDriver()->beginScene()) return false;
		_device->getSceneManager()->drawAll();
		_device->getGUIEnvironment()->drawAll();
		if (!_device->getVideoDriver()->endScene()) return false;
		return true;
	}

	void Menu::unloadContent() {

	}

	void Menu::shutdown() {
		_device->drop();
		_audioEngine->drop();
	}


}