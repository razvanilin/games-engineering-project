#pragma once

#include <unordered_map>
#include <string>
#include "State.h"

namespace GameEngine{
	template <typename T>
	class StateMachine{
	private:
		//The owner of the state machine. Will be an entity in most cases.
		// However, the game can be controlled by this method
		T* _owner;
		//The collection of states mapped against a name
		std::unordered_map<std::string, State<T>*> _states;
		//the current state used by the state machine
		State<T>* _current;

	public:
		//Creates a new state machine
		StateMachine(T* owner) : _owner(owner), _current(0){ }

		//Destructor
		~StateMachine();

		//Adds a state to the state machine
		void addState(const std::string& name, State<T>* state);

		//Gets a particular state stored by the SM
		State<T>* getState(const std::string& name);

		//Removes a state from the SM
		void removeState(const std::string& name);

		//Changes the current state to named state
		void setState(const std::string& name);

		//Calls update on current state
		void update(float deltaTime);
	};

	template <typename T>
	StateMachine<T>::~StateMachine(){
		//iterates through the map stored by SM and deletes contents
		for(auto iter = _states.begin(); iter != _states.end(); ++iter){
			delete iter->second;
			iter->second = 0;
		}
		//now empty
		_states.clear();
		
		//set owner to null
		_owner = 0;

		//set current state to null
		_current = 0;
	}

	template <typename T>
	void StateMachine<T>::addState(const std::string& name, State<T>* state){
		_states[name] = state;
	}

	template <typename T>
	State<T>* StateMachine<T>::getState(const std::string& name){
		auto found = _states.find(name);
		if(found!= _states.end()){
			return found->second;
		}else{
			return 0;
		}
	}

	template <typename T>
	void StateMachine<T>::removeState(const std::string& name){
		auto found = _states.find(name);
		if(found != _states.end()){
			_states.remove(found);	
		}	
	}

	template <typename T>
	void StateMachine<T>::setState(const std::string& name){
		auto found = _states.find(name);
		if(found != _states.end()){
			_current = found->second;	
		}	
	}

	template <typename T>
	void StateMachine<T>::update(float deltaTime){
		if(_current) _current->execute(_owner, deltaTime);	
	}
}