#pragma once

#include <irrlicht.h>
#include <memory>

using namespace irr;
using namespace irr::core;
using namespace irr::gui;

	//defines a structure to store mouse state at any given time.
	struct MouseState{
		position2di Position;
		bool LeftButton;
		bool RightButton;
		bool MiddleButton;
	};

	struct GameState {
		bool GameStarted;
		bool GameClosed;
		bool GamePaused;
		bool GameEnded;
		std::string GameDifficulty;
	};
	
	enum {
		START,
		EXIT,
		EASY,
		MEDIUM,
		HARD
	};

	class InputHandler : public IEventReceiver{
	private:
		bool _keyDown[KEY_KEY_CODES_COUNT];
		bool _prevKeyDown[KEY_KEY_CODES_COUNT];
		MouseState _currentMouse;
		MouseState _prevMouse;
		GameState _gameState;
	public:
		InputHandler(){
			_gameState.GameDifficulty = "easy";

			for (int i = 0; i < KEY_KEY_CODES_COUNT; i++){
				_keyDown[i] = false;
			}
			for (int i = 0; i < KEY_KEY_CODES_COUNT; i++){
				_prevKeyDown[i] = false;
			}
		}

		bool OnEvent(const SEvent& event){
			if (event.EventType == EET_KEY_INPUT_EVENT){
				_keyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
			}
			else if (event.EventType == EET_MOUSE_INPUT_EVENT){
				//check type of mouse event and act accordingly
				switch (event.MouseInput.Event){
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
			else if (event.EventType == EET_GUI_EVENT)
			{
				s32 id = event.GUIEvent.Caller->getID();

				switch (event.GUIEvent.EventType)
				{
				case EGET_BUTTON_CLICKED:
					switch (id)
					{
					case START:
						_gameState.GameStarted = true;
						break;
					case EXIT:
						_gameState.GameClosed = true;
						break;
					case EASY:
						_gameState.GameDifficulty = "easy";
						break;
					case MEDIUM:
						_gameState.GameDifficulty = "medium";
						break;
					case HARD:
						_gameState.GameDifficulty = "hard";
						break;
					default:
						break;
					}
					break;
				default:
					break;
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

		GameState getGameState() {
			return _gameState;
		}

		void setCurrentMouse(int valueX, int valueY) {
			_currentMouse.Position.X = valueX;
			_currentMouse.Position.Y = valueY;
		}

		void setPreviousMouse(int valueX, int valueY) {
			_prevMouse.Position.X = valueX;
			_prevMouse.Position.Y = valueY;
		}

		void update(){
			std::memcpy(_prevKeyDown, _keyDown, sizeof(bool)* KEY_KEY_CODES_COUNT);
			_prevMouse = _currentMouse;
		}
	};
