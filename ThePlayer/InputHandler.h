#pragma once

#include <irrlicht.h>
#include <memory>

using namespace irr;
using namespace irr::core;

//defines a structure to store mouse state at any given time.
struct MouseState{
	position2di Position;
	bool LeftButton;
	bool RightButton;
	bool MiddleButton;
};

class InputHandler : public IEventReceiver{
private: 
	bool _keyDown[KEY_KEY_CODES_COUNT];
	bool _prevKeyDown[KEY_KEY_CODES_COUNT];
	MouseState _currentMouse;
	MouseState _prevMouse;
public:
	InputHandler(){
		for(int i=0; i<KEY_KEY_CODES_COUNT; i++){
			_keyDown[i] = false;
		}
		for(int i=0; i<KEY_KEY_CODES_COUNT; i++){
			_prevKeyDown[i] = false;
		}
	}

	bool OnEvent(const SEvent& event){
		if(event.EventType == EET_KEY_INPUT_EVENT){
			_keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		} else if(event.EventType == EET_MOUSE_INPUT_EVENT){
			//check type of mouse event and act accordingly
			switch(event.MouseInput.Event){
			case EMIE_LMOUSE_PRESSED_DOWN:
				_currentMouse.LeftButton = true;
				break;
			case EMIE_RMOUSE_PRESSED_DOWN:
				_currentMouse.RightButton = true;
				break;
			case EMIE_MMOUSE_PRESSED_DOWN:
				_currentMouse.MiddleButton = true;
				break;
			case EMIE_LMOUSE_LEFT_UP:
				_currentMouse.LeftButton = false;
				break;
			case EMIE_RMOUSE_LEFT_UP:
				_currentMouse.RightButton = false;
				break;
			case EMIE_MMOUSE_LEFT_UP:
				_currentMouse.LeftButton = false;
				break;
			case EMIE_MOUSE_MOVED:
				_currentMouse.Position.X = event.MouseInput.X;
				_currentMouse.Position.Y = event.MouseInput.Y;
			}
		}
		return false;
	}

	bool isKeyDown(EKEY_CODE key) const{
		return _keyDown[key];
	}
	bool wasKeyDown(EKEY_CODE key) const{
		return _prevKeyDown[key];
	}
	MouseState getCurrentMouse(){
		return _currentMouse;
	}

	MouseState getPrevMouse(){
		return _prevMouse;
	}

	void update(){
		std::memcpy(_prevKeyDown, _keyDown, sizeof(bool) * KEY_KEY_CODES_COUNT);
		_prevMouse = _currentMouse;
	}
};
