//#include "Menu.h"
//#include "Game.h"
//#include <sstream>
//#include <iostream>
//#include <string>
//
//using namespace irr::gui;
//using namespace irr::core;
//using namespace irr::video;
//
//GameEngine::Menu menu = GameEngine::Menu();
//InputHandler inputHandler = InputHandler();
//
//namespace GameEngine {
//	bool Menu::initialise() {
//		_device = irr::createDevice(
//			EDT_DIRECT3D9,
//			_dimensions,
//			32,
//			true,
//			false,
//			true,
//			*inputHandler);
//		return true;
//	}
//
//	bool Menu::loadContent() {
//		_env->addButton(recti(vector2di(100, 100), vector2di(300, 300)), 0, 1, L"Button");
//		return true;
//	}
//
//	bool Menu::update(float deltaTime) {
//		dimension2d<u32> dims = game.getDimensions();
//		ITexture* texture = game.getDevice()->getVideoDriver()->getTexture("textures/killer-rabbit.jpg");
//		IGUIImage* img = _env->addImage(texture, position2d<s32>(game.getDimensions().Width, game.getDimensions().Height), false);
//		//_env->addButton(recti(vector2di(100, 100), vector2di(300, 300)), 0, 1, L"Button");
//		//IGUIWindow* wnd = _env->addWindow(rect<s32>(0, 0, dims.Width, dims.Height), false, L"Window", 0, WINDOW);
//
//		return true;
//	}
//
//	bool Menu::render() {
//
//	}
//
//	void Menu::unloadContent() {
//
//	}
//
//	void Menu::shutdown() {
//
//	}
//
//
//}