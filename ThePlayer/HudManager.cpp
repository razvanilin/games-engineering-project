/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#include "HudManager.h"
#include "Game.h"
#include "MessageHandler.h"
#include <iostream>
#include "Player.h"
#include "EntityManager.h"
#include <list>
#include "Collectable.h"
#include <sstream>
#include <string>

using namespace irr::gui;
using namespace irr::core;
using namespace irr::video;


HudManager::HudManager() : Entity(-1, 0, "Hudman"){
	_hintTimer = 0;
	///*setup Hints*/

	_hints["Movement"] = "Use W, A, S & D to move around.";
	_hints["Camera"] = "Look around with the mouse";
	_hints["Throw"] = "Press 'E' again to drop, or left click the mouse to throw";
	_hints["Object"] = "Press 'E' to pick up certain objects";
	_hints["Door"] = "Press 'F' to move through doors";
	_hints["Noise"] = "Wow!\nThat made a lot of noise...";
	_hints["Runaway"] = "Great!\nYou got all your stuff.\nNow get out...\nBefore she wakes up!";
	_hints["Pause"] = "Press'p' to pause.";


	//init hintsShown check map
	std::unordered_map<std::string, std::string>::iterator si = _hints.begin();
	for (; si != _hints.end();si++){
		_hintsShown[si->first] = false;
	}

	//set guiEnvironment
	_env = game.getDevice()->getGUIEnvironment();

	//initilise texture map
	std::list<Entity*>* allColls = EntityManager::getNamedEntities("Collectable");
	auto iter = allColls->begin();
	while (iter != allColls->end()){
		Collectable* collTemp = (Collectable*)(*iter);
		std::wstringstream pathToTexture;
		pathToTexture << "textures/" << collTemp->getItemName().c_str() << ".png";
		ITexture* tempTexture = game.getDevice()->getVideoDriver()->getTexture(pathToTexture.str().c_str());
		_collTextures[collTemp->getItemName()] = tempTexture;
		iter++;
	}
	_font = _env->getFont("bigfont.png");
	_hintText = "";
}



void HudManager::initialise(){

}

void HudManager::loadContent(){

}

void HudManager::update(float deltaTime){
	
	//clear everything
	_env->clear();
	

	//get player
	Player* player = (Player*)EntityManager::getNamedEntities("Player")->front();

	

	//get dimensions
	dimension2d<u32> dims = game.getDimensions();


	//Draw collectables. use of alpha channel depends on if the object has been picked up or not
	int offset = 60;
	int count = 0;
	std::unordered_map<std::string, bool> collectableList = player->getCollectedItems();
	std::unordered_map<std::string, bool>::iterator i = collectableList.begin();
	for (; i != collectableList.end(); i++){
		IGUIImage* img = _env->addImage(_collTextures[i->first], core::position2d<s32>(dims.Width - 100 - (offset*count), 50), false);
		img->setUseAlphaChannel(!i->second); 
		count++;
	}
	//draw label
	IGUIStaticText* CollLabel = _env->addStaticText(L"Possessions:", irr::core::rect<irr::s32>(dims.Width - 100 - (offset*count) + 50, 20, dims.Width - 100 - (offset*count) + 300, 80), false);
	CollLabel->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	CollLabel->setOverrideFont(_font);

	//display hint checks
	if (_hintTimer > 5) _hintTimer = 0;
	if (_hintTimer == 0 && !hasHintBeenShownFor("Movement")){
		drawHintFor("Movement");
	}
	if (_hintTimer == 0 && !hasHintBeenShownFor("Camera")){
		drawHintFor("Camera");
	}
	if (_hintTimer == 0 && !hasHintBeenShownFor("Pause")){
		drawHintFor("Pause");
	}
	if (player->allItemsCollected() && !hasHintBeenShownFor("Runaway")){
		drawHintFor("Runaway");
	}
	if (_hintTimer >= 1 && _hintTimer < 5){
		std::wstringstream sstream;
		sstream << _hintText.c_str();
		IGUIStaticText* text = _env->addStaticText(sstream.str().c_str(), irr::core::rect<irr::s32>(dims.Width / 2 - 200, dims.Height / 2 - 200, dims.Width / 2 + 200, dims.Height / 2 + 200), false);
		text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
		text->setOverrideFont(_font);
	}
	if (_hintTimer >= 1){
		_hintTimer += deltaTime;
	}
	

	//draw noise meter based on players noise allowance - uses a IGUIButton
	ITexture* buttColor;
	if (player->getNoiseAllowance() > 50){
		buttColor = game.getDevice()->getVideoDriver()->getTexture(L"textures/noise_100.png");
	}
	else if (player->getNoiseAllowance() > 20){
		buttColor = game.getDevice()->getVideoDriver()->getTexture(L"textures/noise_50.png");
	}
	else{
		buttColor = game.getDevice()->getVideoDriver()->getTexture(L"textures/noise_20.png");
	}
	IGUIButton* butt = _env->addButton(rect<s32>(20, 50, 20 + (4 * player->getNoiseAllowance()), 100));
	butt->setImage(buttColor);
	butt->setScaleImage(true);
	//draw noise meter - currently text counting from 100	
	std::wstringstream sstream;
	sstream.precision(1);
	sstream << "Noise Allowance: \n";
	IGUIStaticText* noiseMeter = _env->addStaticText(sstream.str().c_str(), irr::core::rect<irr::s32>(20, 20, 620, 50), false);
	noiseMeter->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	noiseMeter->setOverrideFont(_font);

	//DEBUGTEXT
	/*std::wstringstream sstream;
	sstream.precision(1);
	sstream << "Noise Allowance: \n" << fixed << player->getNoiseAllowance();
	IGUIStaticText* noiseMeter = _env->addStaticText(sstream.str().c_str(), irr::core::rect<irr::s32>(20, 20, 620, 120), false);
	noiseMeter->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
	noiseMeter->setOverrideFont(_font);*/











}

void HudManager::render(){

}

void HudManager::unloadContent(){
	
}

void HudManager::shutdown(){
		
}

void HudManager::drawHintFor(std::string hintFor){
	std::string tempHint;
	auto found = _hints.find(hintFor);
	if (found != _hints.end()){
		_hintText = found->second;
		_hintTimer = 1;
		_hintsShown[found->first] = true;
	}
}
