//#pragma once
//
//#include <irrlicht.h>
//#include <irrKlang.h>
//#include <string>
//
//using namespace::irr::gui;
//using namespace irr::core;
//
//namespace GameEngine {
//	class Menu {
//	private:
//		IrrlichtDevice* _device;
//		std::wstring _caption;
//		IGUIEnvironment* _env;
//		IGUIFont* _font;
//		dimension2d<u32> _dimensions;
//		irrklang::ISoundEngine* _audioEngine;
//
//	public:
//		Menu();
//		~Menu(){}
//
//		IrrlichtDevice* getDevice() { return _device; }
//
//		void setCaption(std::wstring value) { _caption = value; }
//
//		dimension2d<u32> getDimensions() { return _dimensions; }
//		void setDimensions(dimension2d<u32> value) { _dimensions = value; }
//
//		irrklang::ISoundEngine* getAudioEngine(){ return _audioEngine; }
//		void setAudioEngine(irrklang::ISoundEngine* val){ _audioEngine = val; }
//
//		bool initialise();
//		bool loadContent();
//		bool update(float deltaTime);
//		bool render();
//		void unloadContent();
//		void shutdown();
//
//	};
//}
//
//extern GameEngine::Menu menu;
//extern InputHandler inputHandler;