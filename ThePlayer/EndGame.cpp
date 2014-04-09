/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "EndGame.h"
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

	EndGame::EndGame(std::string endCause, float noiseMade) {
		_endCause = endCause;
		float _noiseMade = noiseMade;
		std::stringstream winStr;
		winStr.precision(1);
		winStr << "Congratulations!\nYou escaped the morning awkwardness.\nYou made " <<std::fixed<< _noiseMade << " 'units' of noise.";
		_caption["cat"] = "You lose!\nYou were mauled to death by a Cat!";
		_caption["dog"] = "You lose!\nYou were chewed up by the dog!";
		_caption["rabbit"] = "You lose!\nThat's no ordinary rabbit!";
		_caption["fatcat"] = "You lose!\nDon't underestimate a hungry cat.";
		_caption["win"] = winStr.str();
		_caption["lose"] = "You lose!\nYou made too much noise! Enjoy your morning of awkward small talk.";
		_caption["fail"] = "You lose!\nYou made it out, but you left some of your stuff behind...";
		_env = game.getDevice()->getGUIEnvironment();
		_font = _env->getFont("bigfont.png");
		//return true;
	}

	bool EndGame::initialise() {
		return true;
	}

	bool EndGame::loadContent() {
		return true;
	}

	bool EndGame::update(float deltaTime) {
		dimension2d<u32> dims = game.getDimensions();

		// create the background image
		ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/logo.png");
		IGUIImage* img = _env->addImage(texture, position2d<s32>(500, 150), true);
		img->setUseAlphaChannel(true);

		// create buttons
		IGUIButton* exitBtn = _env->addButton(recti(vector2di(100, 200), vector2di(350, 300)), 0, EXIT, L"EXIT");
		exitBtn->setOverrideFont(_font);
		if (inputHandler.getGameState().GameResumed)
			exitBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_PRESSED.c_str()));
		else
			exitBtn->setImage(game.getDevice()->getVideoDriver()->getTexture(BTN_DEFAULT.c_str()));

		std::wstringstream sstream;
		sstream << _caption[_endCause].c_str();
		IGUIStaticText* text = _env->addStaticText(sstream.str().c_str(), rect<s32>(dims.Width / 2 - 200, dims.Height / 2 +50, dims.Width / 2 - 50.0f + 400.0f, dims.Height / 2 - 20 + 400.0f), false);
		text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
		text->setOverrideFont(_font);

		return true;
	}

	void EndGame::unloadContent() {
		_env->clear();
	}
}