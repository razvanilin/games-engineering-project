/*
* Authors:
* Razvan Ilin(40090044) 
* && 
* David Russell(40091149)
* Date: April 2014
*/
#pragma once
#include <irrlicht.h>
#include "Entity.h"
#include <list>
#include <unordered_map>
#include "Entity.h"
using namespace irr::video;

using namespace::irr::gui;
using namespace irr::core;
using namespace GameEngine;

class HudManager : public Entity{
private:
	//store * to the IGUIEnvironment
	IGUIEnvironment* _env;
	//stores textures for all collectables
	std::unordered_map<std::string, ITexture*> _collTextures;
	//used to keep track of how long a hint has been rendered
	float _hintTimer;
	//text to display for on next update
	std::string _hintText;
	//(string*string) map to store hint to store hintname and text to be displayed 
	std::unordered_map<std::string, std::string> _hints;
	//(string*bool) map used to store whether hint has been shown or not
	std::unordered_map<std::string, bool> _hintsShown;
	//font for text
	IGUIFont* _font;

public:
	HudManager();
	~HudManager(){}



	//initialises the HUD
	void initialise();
	//loads content HUD
	void loadContent();
	//update HUD
	void update(float frameTime);
	//Render HUD
	void render();
	//Unloads HUD
	void unloadContent();
	//shuts down HUD
	void shutdown();
	//call to display hint text of string
	void drawHintFor(std::string hintFor);
	//returns whether a hint has been shown for the given string
	bool hasHintBeenShownFor(std::string hintFor){
		auto found = _hintsShown.find(hintFor);
		if (found != _hintsShown.end())
			return found->second;
		//entity doesn't exist - return 0
		return 0;
	}
};

