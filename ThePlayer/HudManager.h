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
	IGUIEnvironment* _env;
	std::unordered_map<std::string, ITexture*> _collTextures;
	float _hintTimer;
	std::string _hintText = "";
	std::unordered_map<std::string, std::string> _hints;
	std::unordered_map<std::string, bool> _hintsShown;
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
	void drawHintFor(std::string hintFor);
	void setHintAsShown(std::string val){ _hintsShown[val] = true; }
	bool hasHintBeenShownFor(std::string hintFor){
		auto found = _hintsShown.find(hintFor);
		if (found != _hintsShown.end())
			return found->second;
		//entity doesn't exist - return 0
		return 0;
	}

	void handleMessage(const Message& message);
};

